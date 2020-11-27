//
// Created by LXH on 2020/10/13.
//

#pragma once

#include <map>
#include <mutex>
#include <vector>

#ifdef __APPLE__
#include <AgoraRtcKit/IAgoraMediaEngine.h>
#include <AgoraRtcKit/IAgoraRtcEngine.h>
#elif __ANDROID__
#include "IAgoraMediaEngine.h"
#include "IAgoraRtcEngine.h"
#endif

namespace agora {
namespace cocos {
class CacheVideoFrame {
public:
  void resetVideoFrame(media::IVideoFrameObserver::VideoFrame &videoFrame);

public:
  int width;
  int height;
  uint8_t *data;
};

class VideoFrameObserver : public media::IVideoFrameObserver {
public:
  VIDEO_FRAME_TYPE getVideoFormatPreference() override;
  bool getRotationApplied() override;
  bool onCaptureVideoFrame(VideoFrame &videoFrame) override;
  bool onRenderVideoFrame(unsigned int uid, VideoFrame &videoFrame) override;

public:
  void bindTextureId(unsigned int textureId, unsigned int uid);

private:
  void cacheVideoFrame(unsigned int uid,
                       media::IVideoFrameObserver::VideoFrame &videoFrame);
  void renderTexture(unsigned int textureId, const CacheVideoFrame &frame);

private:
  std::map<unsigned int, CacheVideoFrame> _map;
  std::mutex mtx;
};
} // namespace cocos
} // namespace agora
