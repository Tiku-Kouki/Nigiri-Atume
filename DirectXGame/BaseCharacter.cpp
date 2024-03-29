﻿#include "BaseCharacter.h"

void BaseCharacter::Initalize(const std::vector<Model*>& models) {

	models_ = models;

	worldTransform_.Initialize();

}

void BaseCharacter::Update() {

	worldTransform_.UpdateMatrix();

}

void BaseCharacter::Draw(ViewProjection& viewProjection) {

for (Model* model : models_) {
	

model->Draw(worldTransform_, viewProjection);

}



}
