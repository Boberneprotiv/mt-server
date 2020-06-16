#include <inttypes.h>
#include "Handle.h"
#include "Light.h"
#include "SparkGeneratorClient.h"

class SparkGenerator {
    private:
        Handle* handle;
        Light* light;

        SparkGeneratorClient* serialClient;

    public:
        SparkGenerator(SparkGeneratorClient* serialClient);
        void update();
};

SparkGenerator::SparkGenerator(SparkGeneratorClient* serialClient) {
    this->serialClient = serialClient;
    this->handle = new Handle(9);
    this->light = new Light(8, 7);
}

void SparkGenerator::update() {
    this->handle->update();
    this->light->update();
    if (this->handle->isActive()) {
        this->serialClient->spark();
        this->light->activate();
    }
}
