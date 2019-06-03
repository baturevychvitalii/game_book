#ifndef __GRAPHICS_STATUS_BAR__
#define __GRAPHICS_STATUS_BAR__

#include "window.h"

namespace graphics
{
    class StatusBar : public Window
    {
        short filled_color;
        size_t act_value;
        size_t max_value;
        
        void ApplyChange() override;
		void DrawSpecific() const override;
        public:
            StatusBar(
                IChangeable * parent,
                size_t width,
                short y,
                short x,
                short empty_color,
                short filled_color,
                size_t act_value,
                size_t max_value);
            
            size_t MinHeight() const override;

            StatusBar & SetMax(size_t maximum);
            StatusBar & SetAct(size_t actual);
    };
}

#endif
