#ifndef MAP_H
#define MAP_H
#define TIMES 20
#define MAP_HEIGHT 45
#define MAP_WIDTH 80
namespace game_framework
{
class Map
{
    public:
        Map();
        //void LoadBitmap();	// 載入地圖
        //void OnShow();		// 顯示地圖
        int IsWhat(int, int, int, int);		
		int Find_PortalLoc(char, int);
        void CreateMap(int, int, int, int, int);
    protected:
        int map[MAP_WIDTH][MAP_HEIGHT];		// 建立地圖矩陣的index
        const int x, y;		// 大地圖的左上角x,y座標
        const int MW, MH;	// 每張小地圖的寬高度
};
}
#endif