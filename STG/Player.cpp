#include "Player.h"

#include "Matrix.h"
#include "Basics.h"
#include "EZDraw.h"
#include "AudioMaster.h"

#include <Novice.h>


Player::Player() {
    pos_ = {300.0f, 360.0f};
    dir_ = { 0.0f, 0.0f };
    speed_ = 8.0f;
    hp_ = 3;
    radius_ = 19.0f;

    points_.p[0] = {pos_.x - 20.0f, pos_.y + 20.0f};
    points_.p[1] = {pos_.x + 20.0f, pos_.y + 10.0f};
    points_.p[2] = {pos_.x - 20.0f, pos_.y - 20.0f};
    points_.p[3] = {pos_.x + 20.0f, pos_.y - 10.0f};

    for (int i = 0; i < 4; i++) {
        screenPoints_.p[i] = { 0.0f, 0.0f };
    }

    for (int i = 0; i < kBulletCount_; i++) {
        bullet_[i] = new Bullet();
    }
    shootTimer_ = { 0, 12 };

    sfxShoot_ = Novice::LoadAudio("./Resources/Audio/shoot.wav");
}

void Player::Update(char* pK, char* k) {
    Matrix* mat = Matrix::GetInstance();
    AudioMaster* am = AudioMaster::GetInstance();

    //デバッグのため
    if (k[DIK_M] && !pK[DIK_M]) {
        hp_--;
    }

    //シュート
    shootTimer_.now++;
    if (k[DIK_SPACE]) {
        //shoot;
        if (shootTimer_.now > shootTimer_.max) {
            for (int i = 0; i < kBulletCount_; i++) {
                if (bullet_[i]->GetBulletShot() == false) {
                    bullet_[i]->SetBulletShot(true);
                    bullet_[i]->SetPos(pos_);
                    shootTimer_.now = 0;
                    am->PlaySFX(sfxShoot_);
                    break;
                }
            }
        }
    }
    dir_ = { 0.0f, 0.0f };
    if (k[DIK_UP]) {
        dir_.y = 1.0f;
    } else if (k[DIK_DOWN]) {
        dir_.y = -1.0f;
    }
    if (k[DIK_LEFT]) {
        dir_.x = -1.0f;
    } else if (k[DIK_RIGHT]) {
        dir_.x = 1.0f;
    }

    //移動
    dir_ = Basics::Normalize(dir_);
    pos_.x += dir_.x * speed_;
    pos_.y += dir_.y * speed_;


    //リミットする
    pos_.x = Basics::Clamp(pos_.x, 0.0f + radius_, 1280.0f - radius_);
    pos_.y = Basics::Clamp(pos_.y, 0.0f + radius_, 720.0f - radius_);

#pragma region バレット

    for (int i = 0; i < kBulletCount_; i++) {
        if (bullet_[i]->GetBulletShot() == true) {
            bullet_[i]->Update();
        }
    }

#pragma endregion 

    //レンダリングのため
    points_.p[0] = { pos_.x - 20.0f, pos_.y + 20.0f };
    points_.p[1] = { pos_.x + 20.0f, pos_.y + 10.0f };
    points_.p[2] = { pos_.x - 20.0f, pos_.y - 20.0f };
    points_.p[3] = { pos_.x + 20.0f, pos_.y - 10.0f };

    //レンダリングパイプライン
    for (int i = 0; i < 4; i++) {
        screenPoints_.p[i] = mat->Transform(points_.p[i]);
    }
}

void Player::Draw() {
    EZDraw::DrawQuad(screenPoints_, WHITE);

    for (int i = 0; i < kBulletCount_; i++) {
        if (bullet_[i]->GetBulletShot() == true) {
            bullet_[i]->Draw();
        }
    }

    //UI
    for (int i = 0; i < hp_; i++) {
        Novice::DrawBox(30 + (30 * i), 30, 20, 40, 0.0f, GREEN, kFillModeSolid);
    }
}

void Player::TakeDamage() {
    hp_--;
}

Bullet Player::GetBullet(int no) {
    return *bullet_[no];
}

int Player::GetBulletCount() {
    return kBulletCount_;
}

int Player::GetHP() {
    return hp_;
}

Vector2 Player::GetPos() {
    return pos_;
}

float Player::GetRadius() {
    return radius_;
}
