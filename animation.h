#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <SDL.h>
#include <vector>
#include <functional>
#include <cassert>
#include <string>

#include "timer.h"
#include "camera.h"
#include "vector2.h"
#include "resourcesManager.h"



class Animation
{
public:
    Animation();
    ~Animation() = default;

    enum class PlayMode
    {
        LOOP,       // 正序循环
        ONCE,       // 单次播放
        REVERSE,    // 逆序循环
        PING_PONG   // 往复播放
    };

    void reset();
    void update(float delta);
    void render(const Camera* camera, const Vector2 base = { 0, 0 }, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
    void addRotation(double angle);

    void addFrame(SDL_Texture* texture, const SDL_Rect& src_rect, float duration);

    void addFramesFromSheet(SDL_Texture* texture, const SDL_Rect& start_rect, const Vector2& frame_size, size_t frame_count, size_t frames_per_row, float duration_per_frame);
    void addFrameFromResource(const std::string& texture_name, const SDL_Rect& src_rect, float duration, bool is_stream = false);

    void addFramesFromSheetResource(const std::string& texture_name, size_t frames_per_row, float duration_per_frame, bool is_stream);

    void clearAndAddFrameFromResource(const std::string& texture_name, const SDL_Rect& src_rect, float duration, bool is_stream = false);
    void clearAndAddFramesFromSheetResource(const std::string& texture_name, size_t frames_per_row, float duration_per_frame, bool is_stream);

    void play();
    void pause();
    void stop();

    void setDstFRect(const SDL_FRect& rect);
    void setPosition(float x, float y);
    void setPosition(const Vector2 position);
    void setRotation(double angle);
    void setScale(const Vector2 scale);
    void setOrigin(const Vector2 origin);
    void setPlayMode(PlayMode mode);
    void setSpeed(float speedFactor);

    void addFinishedAction(std::function<void()> action);
    void addFrameChangedAction(std::function<void()> action);
    void resetFinishedAction();
    void resetFrameChangedAction();

    bool isPlaying() const { return !this->m_paused && !this->m_stopped && !this->m_finished; }
    bool isPaused() const { return this->m_paused; }
    bool isStopped() const { return this->m_stopped; }
    bool isFinished() const { return this->m_finished; }
    SDL_Rect getCurrRect() const;
    SDL_FRect getPosRect() const;
    SDL_Texture* getCurrentTexture() const { return this->m_frames[this->m_frame_index].texture; }

private:
    struct Frame
    {
        SDL_Texture* texture = nullptr;
        SDL_Rect src_rect;
        float duration;

        Frame(SDL_Texture* tex, const SDL_Rect& src, float dur = 1)
            : texture(tex), src_rect(src), duration(dur)
        {

        }
    };

    void calculateNextIndex();
    void triggerCallbacks();

public:
    bool is_show = true;

    SDL_FRect m_dst_rect;
    Vector2 m_scale = { 1.0f, 1.0f }; // 缩放比例
    SDL_FPoint m_origin = { 0.0f, 0.0f };// 动画原点（相对于帧左上角）
    float m_rotation = 0.0f;    // 旋转角度（度）

private:
    std::vector<Frame> m_frames;        // 帧列表
    size_t m_frame_index = 0;          // 当前帧索引

    PlayMode m_play_mode = PlayMode::LOOP;  // 播放模式
    float m_speed_factor = 1.0f;           // 播放倍度
    int m_play_direction = 1;              // 播放方向

    bool m_paused = false;    // 暂停播放
    bool m_stopped = false;    // 结束播放
    bool m_finished = false;  // 播放完成状态（仅ONCE类型有效）

    Timer m_frame_timer;

    std::function<void()> on_finished;//动画播放结束回调（仅ONCE类型有效）
    std::function<void(size_t)> on_frame_changed;//帧切换时回调
};

#endif
