#include "notifications.h"

#include "text.h"

namespace web_ui
{
    int notifications::target_size = 5;
    std::list<std::pair<std::string, std::chrono::steady_clock::time_point>> notifications::texts;
    glm::vec2 notifications::upper_left_corner = {0.45f, 0.95f};

    void notifications::update()
    {
        auto it = texts.begin();
        while (it != texts.end())
        {
            auto now = std::chrono::steady_clock::now();
            if (it->second == std::chrono::steady_clock::time_point{})
                ++it;
            else
            {
                auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - it->second).count();
                if (elapsed >= 0)
                    it = texts.erase(it);
                else
                    ++it;
            }
        }
    }
    
    void notifications::draw()
    {
        update();
        int i = 0;

        // draw backwards (top to bottom)
        if ((int)texts.size() > target_size)
        {
            auto it = texts.begin();
            for (int k = 0; k < target_size; ++k)
                it++;
            for (; it != texts.begin(); --it)
            {
                web_ui::text::draw_text({upper_left_corner.x, upper_left_corner.y - i++ * 0.04f}, (*it).first);
                if (i == target_size)
                    break;
            }
        }
        else
        {
            auto it = texts.end();
            it--;
            for (; it != texts.begin(); --it)
                web_ui::text::draw_text({upper_left_corner.x, upper_left_corner.y - i++ * 0.04f}, (*it).first);
            web_ui::text::draw_text({upper_left_corner.x, upper_left_corner.y - i++ * 0.04f}, texts.begin()->first);
        }
    }

    void notifications::add(std::string text, int duration)
    {
        if (duration > 0)
            texts.push_back({text, std::chrono::steady_clock::now() + std::chrono::seconds(duration)});
        else
            texts.push_back({text, {}});
    }
}
