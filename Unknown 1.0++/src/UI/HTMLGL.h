#ifndef HTMLGL_LIBRARY_H
#define HTMLGL_LIBRARY_H

#include <litehtml.h>
#include <document.h>
#include "GLDocumentContainer.h"

namespace Unknown {
    class HTMLContainer {
        litehtml::glDocumentContainer documentContainer;
        litehtml::context htmlContext;
        litehtml::document::ptr htmlDocument;


    public:
        HTMLContainer(const std::string &str);

        void render();
    };
}

#endif