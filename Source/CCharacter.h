#include "Map.h"
namespace game_framework
{
class CCharacter
{
    public:
        CCharacter();
        int  GetX1();					// 擦子左上角 x 座標
        int  GetY1();					// 擦子左上角 y 座標
        int  GetX2();					// 擦子右下角 x 座標
        int  GetY2();					// 擦子右下角 y 座標
        void Initialize();				// 設定擦子為初始值
        void LoadBitmap();				// 載入圖形
        void OnMove(Map*);					// 移動擦子
        void OnShow();					// 將擦子圖形貼到畫面
        void SetMovingDown(bool flag);	// 設定是否正在往下移動
        void SetMovingLeft(bool flag);	// 設定是否正在往左移動
        void SetMovingRight(bool flag); // 設定是否正在往右移動
        void SetMovingUp(bool flag);	// 設定是否正在往上移動
        void SetXY(int nx, int ny);		// 設定擦子左上角座標
        void jump(Map*);					//設定腳色跳躍
    protected:
        CAnimation animation;		// 擦子的動畫
        int x, y;					// 擦子左上角座標
        int	velocity, initial_velocity;
        bool rising;
        bool isMovingDown;			// 是否正在往下移動
        bool isMovingLeft;			// 是否正在往左移動
        bool isMovingRight;			// 是否正在往右移動
        bool isMovingUp;			// 是否正在往上移動
};
}