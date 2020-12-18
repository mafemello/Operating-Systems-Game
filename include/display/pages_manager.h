#ifndef PAGES
#define PAGES

#include "display_context.h"

class PagesManager {
    public:
        PagesManager(SharedBuffer<DisplayContext> *buffer);

        ~PagesManager();

        bool is_at_last_page();

        void display_page();

        void next_page();

    protected:
        SharedBuffer<DisplayContext> *buffer;
        DisplayContext context;
};

#endif
