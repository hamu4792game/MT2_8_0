#include <Novice.h>
#include "Matrix3x3.h"

const char* kWindowTitle = "MT2_13_0_確認";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	// ライブラリの初期化
	int kWindowWidth = 480, kWindowHeight = 960;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//	行列の作成
	Matrix3x3 cameraMatrix = cameraMatrix.MakeAffineMatrix({ 1.0f,1.0f }, 0.0f, { 240.0f,480.0f });

	Matrix3x3 orthoMatrix = orthoMatrix.MakeOrthographicMatrix({ -240.0f,480.0f }, { 240.0f,-480.0f });

	Matrix3x3 viewportMatrix = viewportMatrix.MakeViewportMatrix({ 0.0f,0.0f }, static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight));

	Vec2 gravity = { 0.0f,-9.8f };

	struct Ball
	{
		Vec2 position;		//	ボールの位置
		Vec2 velocity;		//	ボールの速度
		Vec2 acceleration;	//	ボールの加速度
		float mass;			//	ボールの質量
		float radius;		//	ボールの半径
		unsigned int color;	//	ボールの色
	};
	Ball ball1{
		{160.0f,960},
		{0.0f,0.0f},
		gravity,
		1.0f,
		10.0f,
		0xffffffff
	};
	Ball ball2{
		{320.0f,960},
		{0.0f,0.0f},
		gravity,
		1.0f,
		10.0f,
		0xffffffff
	};

	
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

		//	メインループでボールの速度に加速度を足す
		ball1.velocity.y += ball1.acceleration.y;

		//	ボールの位置に速度を足す
		ball1.position.y += ball1.velocity.y;

		Vec2 airResistance = {
			0.6f * -ball2.velocity.x,0.6f * -ball2.velocity.y
		};

		Vec2 airResistanceAcceleration = { 0.0f,airResistance.y / ball2.mass };

		ball2.acceleration.y = gravity.y + airResistanceAcceleration.y;

		ball2.velocity.y += (ball2.acceleration.y / 60.0f);

		ball2.position.y += (ball2.velocity.y / 60.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		//	座標変換
		Vec2 screenPos = Transform(ball1.position, viewportMatrix);
		Vec2 screenRightTop = Transform(rightTopLocal, wvpVpMatrix);
		Vec2 screenLeftBottom = Transform(leftBottomLocal, wvpVpMatrix);
		Vec2 screenRightBottom = Transform(rightBottomLocal, wvpVpMatrix);

		Novice::DrawQuad(screenLeftTop.x, screenLeftTop.y, screenRightTop.x, screenRightTop.y,
			screenLeftBottom.x, screenLeftBottom.y, screenRightBottom.x, screenRightBottom.y,
			0, 0, 1, 1, white, 0xffffffff);

		Novice::DrawEllipse()

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
