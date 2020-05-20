//
// Created by cub3d on 11/11/18.
//

#include "GLDocumentContainer.h"
#include <Graphics/RenderingBackend.h>
#include <Font/TTFont.h>
#include <SDL_ttf.h>

litehtml::uint_ptr litehtml::glDocumentContainer::create_font(const tchar_t *faceName, int size,
                                                              int weight, font_style italic,
                                                              unsigned int decoration, litehtml::font_metrics *fm) {
    printf("Mk font %s:%d %d\n", faceName, size, weight);

    auto fnt = new Unknown::TTFont("Fonts/" + std::string(faceName), size, Unknown::WHITE);

    fm->height = TTF_FontHeight(fnt->font);
    fm->x_height = fnt->getStringHeight("x");
    fm->ascent = TTF_FontAscent(fnt->font);
    fm->descent = TTF_FontDescent(fnt->font);
    fm->draw_spaces = false;

    return (uint_ptr)fnt;
}

void litehtml::glDocumentContainer::delete_font(litehtml::uint_ptr hFont) {
    delete (Unknown::TTFont*)hFont;
}

int litehtml::glDocumentContainer::text_width(const litehtml::tchar_t *text, litehtml::uint_ptr hFont) {
    //printf("FW: %d\n", x);
    return ((Unknown::TTFont*)hFont)->getStringWidth(std::string(text));
}

void litehtml::glDocumentContainer::draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t *text,
                                              litehtml::uint_ptr hFont, litehtml::web_color color,
                                              const litehtml::position &pos) {
    printf("Draw str: %s %d %d\n", text, pos.x, pos.y);

    ((Unknown::TTFont*)hFont)->drawString(std::string(text), pos.x, pos.y);
}

int litehtml::glDocumentContainer::pt_to_px(int pt) {
    return pt;
}

int litehtml::glDocumentContainer::get_default_font_size() const {
    return 30;
}

void litehtml::glDocumentContainer::draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker &marker) {
    printf("Draw list marker\n");
}

void litehtml::glDocumentContainer::load_image(const litehtml::tchar_t *src, const litehtml::tchar_t *baseurl,
                                               bool redraw_on_ready) {
    printf("Load image\n");
}

void litehtml::glDocumentContainer::get_image_size(const litehtml::tchar_t *src, const litehtml::tchar_t *baseurl,
                                                   litehtml::size &sz) {
    printf("Get img size\n");
}

void litehtml::glDocumentContainer::draw_borders(litehtml::uint_ptr hdc, const litehtml::borders &borders,
                                                 const litehtml::position &draw_pos, bool root) {
    //printf("Draw boarders\n");
}

void litehtml::glDocumentContainer::set_caption(const litehtml::tchar_t *caption) {
    printf("Title is: %s\n", caption);
}

void litehtml::glDocumentContainer::set_cursor(const litehtml::tchar_t *cursor) {
    printf("Set cursor\n");
}

void litehtml::glDocumentContainer::transform_text(litehtml::tstring &text, litehtml::text_transform tt) {
    printf("Text transform\n");
}

void litehtml::glDocumentContainer::import_css(litehtml::tstring &text, const litehtml::tstring &url,
                                               litehtml::tstring &baseurl) {
    printf("Wants some css\n");
}

void litehtml::glDocumentContainer::set_clip(const litehtml::position &pos, const litehtml::border_radiuses &bdr_radius,
                                             bool valid_x, bool valid_y) {
    printf("Set clip\n");
}

void litehtml::glDocumentContainer::del_clip() {
    printf("del clip\n");
}

void litehtml::glDocumentContainer::get_client_rect(litehtml::position &client) const {
    client.x = 0;
    client.y = 0;
    client.width = 5000;
    client.height = 5000;
    //printf("CLR\n");
}

std::shared_ptr<litehtml::element>
litehtml::glDocumentContainer::create_element(const litehtml::tchar_t *tag_name, const litehtml::string_map &attributes,
                                              const std::shared_ptr<litehtml::document> &doc) {

    //printf("Created element %s\n", tag_name);

    return nullptr;
}

void litehtml::glDocumentContainer::get_media_features(litehtml::media_features &media) const {
    media.type = litehtml::media_type_screen;
    media.width = 500;
    media.height = 500;
    media.device_width = 5000;
    media.device_height = 5000;
    media.color = 8;
    media.monochrome = 0;
    media.color_index = 256;
    media.resolution = 96;
}

void litehtml::glDocumentContainer::get_language(litehtml::tstring &language, litehtml::tstring &culture) const {
    printf("Lang\n");
}

void litehtml::glDocumentContainer::on_anchor_click(const litehtml::tchar_t *url, const litehtml::element::ptr &el) {
    printf("Anchor click\n");
}

void
litehtml::glDocumentContainer::link(const std::shared_ptr<litehtml::document> &doc, const litehtml::element::ptr &el) {
    printf("Link\n");
}

void litehtml::glDocumentContainer::set_base_url(const litehtml::tchar_t *base_url) {
    printf("Base url\n");
}

void litehtml::glDocumentContainer::draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint &bg) {
    Unknown::Colour col(bg.color.red, bg.color.green, bg.color.blue, bg.color.alpha);

    if(bg.is_root) {
        auto& ss = Unknown::getUnknown().config.targetSize;
        Unknown::getRendererBackend()->drawRect(0, 0, ss.width, ss.height, 0,col);
    } else {
        Unknown::getRendererBackend()->drawRect(bg.clip_box.x, bg.clip_box.y, bg.clip_box.width, bg.clip_box.height, 0,col);
    }
    printf("BG\n");
}

const litehtml::tchar_t *litehtml::glDocumentContainer::get_default_font_name() const {
    return "Arimo-Regular.ttf";
}
