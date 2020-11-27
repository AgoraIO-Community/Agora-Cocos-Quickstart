// Learn cc.Class:
//  - https://docs.cocos.com/creator/manual/en/scripting/class.html
// Learn Attribute:
//  - https://docs.cocos.com/creator/manual/en/scripting/reference/attributes.html
// Learn life-cycle callbacks:
//  - https://docs.cocos.com/creator/manual/en/scripting/life-cycle-callbacks.html

var AgoraVideoRender = cc.Class({
    extends: cc.Component,
    properties: {
        sprite: {
            default: null,
            type: cc.Sprite
        },
        uid: 0
    },
    // LIFE-CYCLE CALLBACKS:
    onLoad() {
        console.log('onLoad', this.uid, this.node.width, this.node.height);
        this.texture = new cc.Texture2D();
        this.texture.initWithData(null, cc.Texture2D.PixelFormat.RGBA8888, this.node.width, this.node.height);
        this.sprite.spriteFrame = new cc.SpriteFrame(this.texture);
    },
    _updateSize() {
        console.log('_updateSize', this.node.width, this.node.height);
        this.texture.width = this.node.width;
        this.texture.height = this.node.height;
    },
    onEnable() {
        this.node.on('size-changed', this._updateSize, this)
    },
    onDisable() {
        this.node.off('size-changed', this._updateSize, this)
    },
    update(dt) {
        if (agora && agora.bridge && agora.bridge.bindTextureId) {
            agora.bridge.bindTextureId(this.texture.getImpl().getHandle(), this.uid);
        }
    },
});