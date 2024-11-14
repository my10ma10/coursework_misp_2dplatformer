#pragma once
//view
View view(Vector2f(0.0f, 0.0f), Vector2f(view_height, view_height));


void changeViewZoom(View& view) {
    if (Keyboard::isKeyPressed(Keyboard::Equal)) {
        view.zoom(0.995f);
    }
    if (Keyboard::isKeyPressed(Keyboard::Dash)) {
        view.zoom(1.005f);
    }
}

void changeViewAspectRatio(const RenderWindow& window, View& view)
{
    float aspect_ratio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(aspect_ratio * view_height, view_height);
}



/*void levelCollision(Collider backgroundCollider) {
	Vector2f backgroundColliderPos = backgroundCollider.getPosition();
	Vector2f backgroundColliderHalfSize = backgroundCollider.getHalfSize();
	Vector2f thisPos = getPosition();
	Vector2f thisHalfSize = getHalfSize();

	Vector2f delta(backgroundColliderPos.x - thisPos.x, backgroundColliderPos.y - thisPos.y);
	Vector2f intersect(thisHalfSize.x - backgroundColliderHalfSize.x - abs(delta.x), \
		thisHalfSize.y - backgroundColliderHalfSize.y - abs(delta.y));

	if (intersect.x < 0.0f || intersect.y < 0.0f) {
		if (intersect.x < intersect.y) {
			if (delta.x > 0.0f) { //right
				Move(-intersect.x, 0.0f);

			}
			else {//left
				Move(intersect.x, 0.0f);
			}
		}
		else {
			if (delta.y > 0.0f) {//down
				Move(0.0f, -intersect.y);
			}
			else {//up
				Move(0.0f, intersect.y);
			}
		}
	}
}*/