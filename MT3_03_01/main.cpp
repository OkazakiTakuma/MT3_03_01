#include "Matrix.h"
#include "Screen3.h"
#include "Vector3.h"
#include <Novice.h>
#include <algorithm>
#include <imgui.h>
const char kWindowTitle[] = "LD2B_01_オカザキ_タクマ";
static const int kRowHeight = 20;
static const int kColumnWidth = 60;
static const float p = 3.1415f;
static const int kWindowsWidth = 1280;
static const int kWindowsHeight = 720;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowsWidth, kWindowsHeight);
	Vector3 rotate = {0.0f, 0.0f, 0.0f};
	Vector3 translate = {0.0f, 0.0f, 0.0f};
	Vector3 cameraPosition = {0.0f, 2.500f, -3.600f};
	Vector3 cameraRotate = {0.7f, 0.0f, 0.0f};

	Vector3 controlpoint[3] = {
	    {-0.8f, 0.58f, 1.0f},
	    {1.76f, 1.0f, -0.3f},
	    {0.94f, -0.7f, 2.3f},
	};
	

	// 衝突判定の結果を受け取る箱
	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	int mousePosX = 0;
	int mousePosY = 0;
	int triggerMousePosX = 0;
	int triggerMousePosY = 0;
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		Novice::GetMousePosition(&mousePosX, &mousePosY);
		cameraPosition.z += Novice::GetWheel() / 100.0f;

		if (keys[DIK_LSHIFT]) {
			if (Novice::IsPressMouse(0)) {
				if (mousePosX - triggerMousePosX > 10) {
					cameraRotate.y -= 0.01f;
				} else if (mousePosX - triggerMousePosX < 0) { // 修正: -0 を 0 に
					cameraRotate.y += 0.01f;
				}

				if (mousePosY - triggerMousePosY > 10) {
					cameraRotate.x -= 0.01f;
				} else if (mousePosY - triggerMousePosY < -10) { // 修正: mousePosX → mousePosY
					cameraRotate.x += 0.01f;
				}
			} else {
				triggerMousePosX = mousePosX;
				triggerMousePosY = mousePosY;
			}
		}
		///
		/// ↓更新処理ここから
		///

		// ポリゴンの更新処理
		if (keys[DIK_R]) {
			cameraRotate.x = 0.0f;
			cameraRotate.y = 0.0f;
		}

		if (keys[DIK_Q]) {
		}
		if (keys[DIK_E]) {
		}
		if (keys[DIK_UP]) {
		}
		if (keys[DIK_DOWN]) {
		}
		if (keys[DIK_LEFT]) {
		}
		if (keys[DIK_RIGHT]) {
		}
		Matrix4x4 worldMatrix = MakeAffineMatrix(Vector3{1.0f, 1.0f, 1.0f}, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix(Vector3{1.0f, 1.0f, 1.0f}, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowsWidth) / float(kWindowsHeight), 0.1f, 100.0f);
		Matrix4x4 wvpMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewPortMatrix = MakeViewportMatrix(0, 0, float(kWindowsWidth), float(kWindowsHeight), 0.0f, 1.0f);
		// 衝突判定
		// 球とOBBの衝突判定
	
		// 衝突判定
	

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		ImGui::Begin("window");
		ImGui::DragFloat3("Camera Position", &cameraPosition.x, 0.1f);
		ImGui::DragFloat3("Camera Rotate", &cameraRotate.x, 0.1f);
		ImGui::DragFloat3("controlpoint0", &controlpoint[0].x, 0.1f);
		ImGui::DragFloat3("controlpoint1", &controlpoint[1].x, 0.1f);
		ImGui::DragFloat3("controlpoint2", &controlpoint[2].x, 0.1f);

		ImGui::End();

		// VectorScreenPrintf(-20, 0, cross, "Cross");
		DrawGrid(wvpMatrix, viewPortMatrix);
		DrawBezier(controlpoint[0], controlpoint[1], controlpoint[2], wvpMatrix, viewPortMatrix, BLUE);
		Sphere point[3] = {
		    {controlpoint[0], 0.01f},
		    {controlpoint[1], 0.01f},
		    {controlpoint[2], 0.01f},
		};
		DrawSphere(point[0], wvpMatrix, viewPortMatrix, BLACK);
		DrawSphere(point[1], wvpMatrix, viewPortMatrix, BLACK);
		DrawSphere(point[2], wvpMatrix, viewPortMatrix, BLACK);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
