#include "HTMLGL.h"

#include "GLDocumentContainer.h"

#include <fstream>
#include <Filesystem/Filesystem.h>
#include <Unknown.h>

Unknown::HTMLContainer::HTMLContainer(const std::string &str) {
    this->htmlDocument = litehtml::document::createFromString(Filesystem::readFile(str).getString().c_str(), &documentContainer, &htmlContext);
}

void Unknown::HTMLContainer::render() {
    auto& ss = getUnknown().config.targetSize;

    this->htmlDocument->render(ss.width);

    litehtml::position p;
    p.x = 0;
    p.y = 0;
    p.width = ss.width;
    p.height = ss.height;

    htmlDocument->draw(nullptr, 0, 0, &p);
}