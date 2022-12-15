#include <Novice.h>
#include "Matrix3x3.h"

const char* kWindowTitle = "MT2_8_0_確認";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	// ライブラリの初期化
	int kWindowWidth = 1280, kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//	player
	Vec2 playerpos = { 0.0f,0.0f };

	Matrix3x3 cameraWorldMatrix;
	cameraWorldMatrix.MakeTranslateMatrix({400.0f,400.0f });

	//	ローカル空間上の座標
	Vec2 leftTopLocal = { -80.0f,80.0f };
	Vec2 rightTopLocal = { 80.0f,80.0f };
	Vec2 leftBottomLocal = { -80.0f,-80.0f };
	Vec2 rightBottomLocal = { 80.0f,-80.0f };

	//	行列の作成
	Matrix3x3 worldMatrix;
	Matrix3x3 viewMatrix;
	viewMatrix.Inverse(cameraWorldMatrix);

	Matrix3x3 orthoMatrix;
	orthoMatrix.MakeOrthographicMatrix({ -640.0f,360.0f }, { 640.0f,-360.0f });
	Matrix3x3 viewportMatrix;
	viewportMatrix.MakeViewportMatrix({ 0.0f,0.0f }, kWindowWidth, kWindowHeight);
	Matrix3x3 wvpVpMatrix;

	int white = Novice::LoadTexture("./white1x1.png");

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (keys[DIK_UP])
		{
			playerpos.y += 10;
		}
		
		if (keys[DIK_DOWN])
		{
			playerpos.y -= 10;
		}

		if (keys[DIK_LEFT])
		{
			playerpos.x -= 10;
		}

		if (keys[DIK_RIGHT])
		{
			playerpos.x += 10;
		}

		//	平行移動更新
		worldMatrix.MakeTranslateMatrix(playerpos);

		//	行列の連携
		wvpVpMatrix = worldMatrix * viewMatrix * orthoMatrix * viewportMatrix;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		//	座標変換
		Vec2 screenLeftTop = Transform(leftTopLocal, wvpVpMatrix);
		Vec2 screenRightTop = Transform(rightTopLocal, wvpVpMatrix);
		Vec2 screenLeftBottom = Transform(leftBottomLocal, wvpVpMatrix);
		Vec2 screenRightBottom = Transform(rightBottomLocal, wvpVpMatrix);

		Novice::DrawQuad(screenLeftTop.x, screenLeftTop.y, screenRightTop.x, screenRightTop.y,
			screenLeftBottom.x, screenLeftBottom.y, screenRightBottom.x, screenRightBottom.y,
			0, 0, 1, 1, white, 0xffffffff);

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
