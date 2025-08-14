#include "animation.h"
#include "resourcesManager.h"

#include <SDL_render.h>
#include <cmath>

Animation::Animation()
{
    this->m_frame_timer.setCallback([this]()
        {
            this->calculateNextIndex();
            this->triggerCallbacks();
        });
}

void Animation::reset()
{
    this->m_frame_index = 0;
    this->m_play_direction = 1;
    this->m_paused = false;
    this->m_stopped = true;
    this->m_finished = false;

    this->m_frame_timer.reset();
    if (!this->m_frames.empty())
    {
        this->m_frame_timer.setDuration(this->m_frames[0].duration);
    }
}

void Animation::update(float delta)
{
    if (this->m_paused || this->m_stopped || this->m_finished || this->m_frames.empty()) return;

    const float adjusted_delta = delta * this->m_speed_factor;

    if (this->m_play_mode == PlayMode::LOOP || this->m_play_mode == PlayMode::PING_PONG || this->m_play_mode == PlayMode::REVERSE)
    {
        if (this->m_frame_timer.isReached()) this->m_frame_timer.reset();
    }
    this->m_frame_timer.update(adjusted_delta);
}

void Animation::render(const Camera* camera, const Vector2 base, SDL_RendererFlip flip) const
{
    if (this->m_frames.empty() || this->m_stopped || !this->is_show) return;

    const Vector2 frame_size = { (float)this->m_dst_rect.w, (float)this->m_dst_rect.h };
    const Vector2 scaled_size = { frame_size.m_x * this->m_scale.m_x, frame_size.m_y * this->m_scale.m_y };
    const Vector2 origin_offset = { this->m_origin.x * m_scale.m_x, this->m_origin.y * m_scale.m_y };

    const float screen_x = this->m_dst_rect.x - camera->m_position.m_x;
    const float screen_y = this->m_dst_rect.y - camera->m_position.m_y;

    SDL_FRect dest_rect = { screen_x + base.m_x, screen_y + base.m_y, scaled_size.m_x, scaled_size.m_y };

    const SDL_FPoint rotation_center = { origin_offset.m_x, origin_offset.m_y };

    SDL_RenderCopyExF(camera->m_renderer, this->getCurrentTexture(), &this->m_frames[this->m_frame_index].src_rect, &dest_rect, this->m_rotation, &rotation_center, flip);
}

void Animation::addRotation(double angle)
{
    this->m_rotation += angle;

    m_rotation = fmod(m_rotation, 360.0);
    if (m_rotation < 0)
    {
        m_rotation += 360.0;
    }
}

void Animation::addFrame(SDL_Texture* texture, const SDL_Rect& src_rect, float duration)
{
    this->m_frames.emplace_back(texture, src_rect, duration);
    
    if (this->m_frames.size() == 1)
    {
        this->m_frame_timer.setDuration(duration);
        this->m_frame_timer.setAutoRestart(false);
    }
}

void Animation::addFramesFromSheet(SDL_Texture* texture, const SDL_Rect& start_rect, const Vector2& frame_size, size_t frame_count, size_t frames_per_row, float duration_per_frame)
{
    for (size_t i = 0; i < frame_count; i++)
    {
        SDL_Rect frame_rect = { start_rect.x + i * frame_size.m_x, start_rect.y, frame_size.m_x, frame_size.m_y };

        this->addFrame(texture, frame_rect, duration_per_frame);
    }
}

void Animation::addFrameFromResource(const std::string& texture_name, const SDL_Rect& src_rect, float duration, bool is_stream)
{
    SDL_Texture* texture = ResourcesManager::getInstance()->queryTexture(texture_name, is_stream);
    this->addFrame(texture, src_rect, duration);
}

void Animation::addFramesFromSheetResource(const std::string& texture_name, size_t frames_per_row, float duration_per_frame, bool is_stream)
{
    SDL_Texture* texture = ResourcesManager::getInstance()->queryTexture(texture_name, is_stream);
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

    this->addFramesFromSheet(texture, { 0, 0, 0, 0 }, { (float)(w / frames_per_row), (float)h }, frames_per_row, frames_per_row, duration_per_frame);
}

void Animation::clearAndAddFrameFromResource(const std::string& texture_name, const SDL_Rect& src_rect, float duration, bool is_stream)
{
    this->m_frames.clear();
    this->addFrameFromResource(texture_name, src_rect, duration, is_stream);
}

void Animation::clearAndAddFramesFromSheetResource(const std::string& texture_name, size_t frames_per_row, float duration_per_frame, bool is_stream)
{
    this->m_frames.clear();
    this->addFramesFromSheetResource(texture_name, frames_per_row, duration_per_frame, is_stream);
}

void Animation::play()
{
    if (this->m_frames.empty()) return;

    if (this->m_finished || this->m_stopped)
    {
        this->m_frame_timer.reset();
        this->m_frame_timer.setDuration(this->m_frames[this->m_frame_index].duration);
    }

    this->m_paused = false;
    this->m_stopped = false;
    this->m_finished = false;
    this->m_frame_timer.start();
}

void Animation::pause()
{
    if (this->isPlaying())
    {
        this->m_paused = true;
        this->m_frame_timer.pause();
    }
}

void Animation::stop()
{
    this->m_stopped = true;
    this->m_paused = false;
    this->m_finished = false;
    this->m_frame_index = std::max((int)(this->m_frames.size() - 1), 0);
    this->m_frame_timer.reset();
}

void Animation::setDstFRect(const SDL_FRect& rect)
{
    this->m_dst_rect = rect;
}

void Animation::setPosition(float x, float y)
{
    this->m_dst_rect.x = x;
    this->m_dst_rect.y = y;
}

void Animation::setPosition(const Vector2 position)
{
    this->m_dst_rect.x = position.m_x;
    this->m_dst_rect.y = position.m_y;
}

void Animation::setRotation(double angle)
{
    this->m_rotation = fmod(angle, 360.0);
    if (this->m_rotation < 0)
    {
        this->m_rotation += 360.0;
    }
}

void Animation::setScale(const Vector2 scale)
{
    this->m_scale = { std::max(0.001f, scale.m_x), std::max(0.001f, scale.m_y) };
}

void Animation::setOrigin(const Vector2 origin)
{
    this->m_origin = { (float)origin.m_x, (float)origin.m_y };
}

void Animation::setPlayMode(PlayMode mode)
{
    switch (mode)
    {
    case PlayMode::LOOP:
    {
        this->m_frame_index = 0;
        this->m_play_direction = 1;
    }
        break;
    case PlayMode::ONCE:
    {
        this->m_frame_index = 0;
        this->m_play_direction = 1;
    }
        break;
    case PlayMode::PING_PONG:
    {
        this->m_frame_index = 0;
        this->m_play_direction = 1;
    }
        break;
    case PlayMode::REVERSE:
    {
        this->m_frame_index = this->m_frames.size() - 1;
        this->m_play_direction = -1;
    }
        break;
    }
    this->m_play_mode = mode;
}

void Animation::setSpeed(float speed_factor)
{
    this->m_speed_factor = speed_factor;
}

void Animation::addFinishedAction(std::function<void()> action)
{
    std::function<void()> old_action = this->on_finished;
    this->on_finished = [old_action, action]()
        {
            if (old_action) old_action();
            action();
        };
}

void Animation::addFrameChangedAction(std::function<void()> action)
{
    std::function<void(size_t)> old_action = this->on_frame_changed;
    this->on_frame_changed = [old_action, action](size_t t)
        {
            if (old_action) old_action(t);
            action();
        };
}

void Animation::resetFinishedAction()
{
    this->on_finished = []() { };
}

void Animation::resetFrameChangedAction()
{
    this->on_frame_changed = [](size_t t) {};
}

SDL_Rect Animation::getCurrRect() const
{
    if (this->m_frames.empty()) return { 0,0,0,0 };

    return this->m_frames[this->m_frame_index].src_rect;
}

SDL_FRect Animation::getPosRect() const
{
    return this->m_dst_rect;
}

void Animation::calculateNextIndex()
{
    if (this->m_frames.empty()) return;

    switch (this->m_play_mode)
    {
    case PlayMode::LOOP:
        this->m_frame_index = (this->m_frame_index + 1) % this->m_frames.size();
        break;
    case PlayMode::ONCE:
        if (this->m_frame_index < this->m_frames.size() - 1)
        {
            this->m_frame_index++;
        }
        else
        {
            this->m_finished = true;
            this->m_stopped = true;
            this->m_frame_timer.pause();
        }
        break;
    case PlayMode::REVERSE:
        this->m_frame_index = ((this->m_frame_index == 0) ? this->m_frames.size() : this->m_frame_index) - 1;
        break;
    case PlayMode::PING_PONG:
        this->m_frame_index += this->m_play_direction;
        if (this->m_frame_index == 0 || this->m_frame_index == this->m_frames.size() - 1)
        {
            this->m_play_direction *= -1;
        }
        break;
    }

    this->m_frame_index = std::max((int)(this->m_frame_index), 0);
    this->m_frame_index = std::min((int)this->m_frame_index, (int)(this->m_frames.size() - 1));
}

void Animation::triggerCallbacks()
{
    if (this->on_frame_changed) this->on_frame_changed(this->m_frame_index);

    if (!this->m_finished)
    {
        this->m_frame_timer.reset();
        this->m_frame_timer.setDuration(this->m_frames[this->m_frame_index].duration);
        this->m_frame_timer.start();
    }

    if (this->m_finished && this->on_finished) this->on_finished();
}
