#include "application.h"

namespace app {

Application::Application()
    : renderer_(Height{RunTime::kScreenHeight}, Width{RunTime::kScreenWidth}), world_(),
      camera_(kCameraHeight, kCameraWidth, kCameraFrontDistance, kCameraBackDistance, kCameraFocus),
      light_(kLightIntensity, kLightDirection), runtime_(), view_(runtime_.window()) {
}

void Application::add_object(ObjectPtr &&object_ptr) {
    world_.objects.push_back(std::move(object_ptr));
}

void Application::run() {
    while (runtime_.is_running()) {
        runtime_.run(camera_, light_);
        Screen screen = renderer_.render(world_, camera_, light_);
        view_.show(std::move(screen));
    }
}

const Point Application::kCameraFocus = Point{0, 0, -20};
const Vector3 Application::kLightDirection = Vector3{0, 0, 1};

} // namespace app
