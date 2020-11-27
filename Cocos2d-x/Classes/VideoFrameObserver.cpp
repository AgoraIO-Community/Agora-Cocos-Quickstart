//
// Created by LXH on 2020/10/13.
//

#include "VideoFrameObserver.h"

#if defined(__ANDROID__)
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined(__APPLE__)
#include <OpenGLES/ES2/gl.h>
#endif

namespace agora {
namespace cocos {
void CacheVideoFrame::resetVideoFrame(
    media::IVideoFrameObserver::VideoFrame &videoFrame) {
  auto size = videoFrame.width * videoFrame.height * 4;
  if (size != width * height * 4) {
    if (data) {
      delete[] data;
      data = new uint8_t[size];
    } else {
      data = new uint8_t[size];
    }
  }
  memcpy(data, videoFrame.yBuffer, size);
  width = videoFrame.width;
  height = videoFrame.height;
}

media::IVideoFrameObserver::VIDEO_FRAME_TYPE
VideoFrameObserver::getVideoFormatPreference() {
  return FRAME_TYPE_RGBA;
}

bool VideoFrameObserver::getRotationApplied() { return true; }

bool VideoFrameObserver::onCaptureVideoFrame(
    media::IVideoFrameObserver::VideoFrame &videoFrame) {
  cacheVideoFrame(0, videoFrame);
  return true;
}

bool VideoFrameObserver::onRenderVideoFrame(
    unsigned int uid, media::IVideoFrameObserver::VideoFrame &videoFrame) {
  cacheVideoFrame(uid, videoFrame);
  return true;
}

void VideoFrameObserver::bindTextureId(unsigned int textureId,
                                       unsigned int uid) {
  if (_map.find(uid) != _map.end()) {
    renderTexture(textureId, _map[uid]);
  }
}

void VideoFrameObserver::cacheVideoFrame(
    unsigned int uid, media::IVideoFrameObserver::VideoFrame &videoFrame) {
  if (_map.find(uid) == _map.end()) {
    _map[uid] = CacheVideoFrame();
  }
  mtx.lock();
  _map[uid].resetVideoFrame(videoFrame);
  mtx.unlock();
}

void VideoFrameObserver::renderTexture(unsigned int textureId,
                                       const CacheVideoFrame &frame) {
  mtx.lock();
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frame.width, frame.height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, frame.data);
  glBindTexture(GL_TEXTURE_2D, 0);
  mtx.unlock();
}
} // namespace cocos
} // namespace agora
