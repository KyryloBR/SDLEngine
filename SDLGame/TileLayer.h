 #ifndef TILEPLAYER_H_
#define TILEPLAYER_H_

#include "Layer.h"
#include "Tileset.h"
#include "Vector2D.h"

class TileLayer : public Layer
{
public:
	TileLayer(int tileSize, const std::vector<Tileset> & tilesets);

	virtual void update();
	virtual void render();

	void setTileIDs(const std::vector<std::vector<int>> & data);
	std::vector<std::vector<int>> & getTileIDs()  { return m_tileIDs; }
	void setTileSize(int nSize);
	void setColumns(int nColumns) { m_nColumnIncrement += nColumns; }

	Vector2D getPosition() { return m_position; }

	int getNumColumns() { return m_nColumns; }
	int getNumRows() { return m_nRows; }
	int getTileSize() { return m_tileSize; }
	int getColumnIncrement() { return m_nColumnIncrement; }

	Tileset getTilesetByID(int tileID);

private:
	int m_nColumns;
	int m_nRows;
	int m_tileSize;
	int m_nColumnIncrement;

	Vector2D m_position;
	Vector2D m_velocity;

	const std::vector<Tileset> * m_tilesets;
	std::vector<std::vector<int>> m_tileIDs;
};



#endif // TILEPLAYER_H_