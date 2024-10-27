#pragma once
//view
View view(Vector2f(0.0f, 0.0f), Vector2f(view_height, view_height));


void changeView(View& view) {
    if (Keyboard::isKeyPressed(Keyboard::Equal)) {
        view.zoom(0.995f);
    }
    if (Keyboard::isKeyPressed(Keyboard::Dash)) {
        view.zoom(1.005f);
    }
}

void resizeView(const RenderWindow& window, View& view)
{
    float aspect_ratio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(aspect_ratio * view_height, view_height);
}

void setViewBorders(View& view, Player player) {
    float tempX = player.getPosition().x;
    float tempY = player.getPosition().y;
    if (player.getBody().getPosition().y < 191.0f) {
        tempX = 191.0f;
    }
    if (player.getBody().getPosition().x < 195.0f) {
        tempY = 195.0f;
    }
    view.setCenter(tempX, tempY);
}