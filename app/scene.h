#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QTimer>

class ComponentItem;
class QUndoStack;
class Wire;

class Scene : public QGraphicsScene
{
    Q_OBJECT

    public:
        Scene();
        ~Scene();

        QList<ComponentItem*> selectedComponents();
        QList<Wire*> selectedWires();
        ComponentItem *selectedComponent();

        bool showGrid() const;
        bool snapToGrid() const;
        int gridSize() const;

        bool isModified() const { return m_modified; }

        bool canUndo() const;
        bool canRedo() const;

    signals:
        void modificationChanged(bool modified);
        void canRedoChanged(bool canRedo);
        void canUndoChanged(bool canUndo);

    public slots:
        void deleteSelection();
        void showProperties();
        void clear();

        void setShowGrid(bool value);
        void setSnapToGrid(bool value);
        void setGridSize(const int &size);
        void setModified(bool modified);

        void alignLeft();
        void alignCenter();
        void alignRight();
        void alignTop();
        void alignMiddle();
        void alignBottom();

        void rotateClockwise();
        void rotateAnticlockwise();

        void flipVertical();
        void flipHorizontal();

        void undo();
        void redo();

    protected:
        void drawBackground(QPainter *painter, const QRectF &rect);
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
        void dropEvent(QGraphicsSceneDragDropEvent *event);
        void dragMoveEvent(QGraphicsSceneDragDropEvent *event);

    private:
        Wire *m_wire;
        QUndoStack *m_undoStack;
        bool m_modified;
};

#endif // SCENE_H
