#ifndef __GRAPHICS_TEXTBOX__
#define __GRAPHICS_TEXTBOX__

#include <vector>
#include <string>
#include "window.h"

namespace graphics
{
    class Textbox : public Window
    {
        std::vector<std::pair<std::string, short>> lines;
        void ApplyChange() override;
        virtual size_t TopIndent() const;
		protected:
			void DrawSpecific() const override;
			void DrawLines() const;
        public:
            Textbox(IChangeable * parent, size_t width, short y, short x, short color);
            Textbox(const Textbox & tb) = delete;
            Textbox & operator=(const Textbox & tb) = delete;

            size_t MinHeight() const override;
            
            size_t SizeLines() const;
            Textbox & InsertText(size_t idx, const std::string & text, short color = -1);
            Textbox & AppendText(const std::string & text, short color = -1);
            size_t NewLine(const std::string & text = "", short color = -1);
            Textbox & AlterLineText(size_t idx, const std::string & new_text);
            Textbox & AlterLineColor(size_t idx, short color);
			Textbox & SwitchLinesColor(short from_this, short to_that);
            Textbox & EraseLines(size_t idx, size_t n = 1);
            Textbox & Clear();
            const std::string & LineAt(size_t idx) const;
            std::string GetText(char delim_lines = ' ') const;        
    };
}

#endif
