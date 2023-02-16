#include <Novice.h>
#include "Matrix3x3.h"
#include <math.h>

const char* kWindowTitle = "MT2_13_0_確認";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	// ライブラリの初期化
	int kWindowWidth = 1280, kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//	行列の作成
	Matrix3x3 cameraMatrix = cameraMatrix.MakeAffineMatrix({ 1.0f,1.0f }, 0.0f, { 440.0f,160.0f });

	Matrix3x3 viewMatrix = viewMatrix.Inverse(cameraMatrix);

	Matrix3x3 orthoMatrix = orthoMatrix.MakeOrthographicMatrix({ -640.0f,360.0f }, { 640.0f,-360.0f });

	Matrix3x3 viewportMatrix = viewportMatrix.MakeViewportMatrix({ 0.0f,0.0f }, static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight));

	Matrix3x3 wvpVpMatrix;

	Vec2 gravity = { 0.0f,-9.8f };
	float miu = 0.4f;
	float magnitude = 0.0f;
	Vec2 direction = { 0.0f,0.0f };
	Vec2 frictionalForce = { 0.0f,0.0f };


	struct Box
	{
		Vec2 position;		//	ボールの位置
		Vec2 size;			//	ボールの半径
		Vec2 velocity;		//	ボールの速度
		Vec2 acceleration;	//	ボールの加速度
		float mass;			//	ボールの質量
		unsigned int color;	//	ボールの色
	};
	Box box{
		{50.0f,50.0f},
		{100.0f,100.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},
		10.0f,
		0xffffffff
	};


	bool flag = false;

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

		if (keys[DIK_SPACE] != 0 && preKeys[DIK_SPACE] == 0)
		{
			box.velocity.x = 70.0f;
			flag = true;
		}

		if (flag)
		{

			magnitude = miu * (-box.mass * gravity.y);

			if (box.velocity.x > 0.0f)
			{
				direction.x = -1.0f;
			}
			else if (box.velocity.x < 0.0f)
			{
				direction.x = 1.0f;
			}

			frictionalForce = { magnitude * direction.x,0.0f };

			box.acceleration.x = frictionalForce.x / box.mass;


			if (fabsf(box.acceleration.x / 60.0f) > fabsf(box.velocity.x))
			{
				box.acceleration.x = box.velocity.x * 60.0f;
			}

			box.velocity.x += (box.acceleration.x / 60.0f);

			box.position.x += (box.velocity.x / 60.0f);

		}

		

		wvpVpMatrix = viewMatrix * orthoMatrix * viewportMatrix;


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		//	座標変換
		Vec2 screenPos = Transform(box.position, wvpVpMatrix);
		
		Vec2 screenLine1 = Transform({ static_cast<float>(-(kWindowWidth)),0.0f }, wvpVpMatrix);
		Vec2 screenLine2 = Transform({ static_cast<float>((kWindowWidth)),0.0f }, wvpVpMatrix);
		Vec2 screenLine3 = Transform({ 0.0f,static_cast<float>(-(kWindowHeight)) }, wvpVpMatrix);
		Vec2 screenLine4 = Transform({ 0.0f,static_cast<float>((kWindowHeight)) }, wvpVpMatrix);

		Novice::DrawLine(screenLine1.x, screenLine1.y, screenLine2.x, screenLine2.y, 0xff0000ff);
		Novice::DrawLine(screenLine3.x, screenLine3.y, screenLine4.x, screenLine4.y, 0x00ff00ff);


		Novice::DrawQuad(screenPos.x - (box.size.x / 2), screenPos.y - (box.size.y / 2),
			screenPos.x + (box.size.x / 2), screenPos.y - (box.size.y / 2),
			screenPos.x - (box.size.x / 2), screenPos.y + (box.size.y / 2),
			screenPos.x + (box.size.x / 2), screenPos.y + (box.size.y / 2),
			0, 0, 1, 1, white, box.color);

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
