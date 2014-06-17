#include "scene.h"

#include "componentmimedata.h"
#include "component.h"
#include "outputpin.h"
#include "inputpin.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPathItem>
#include <QDragEnterEvent>
#include <QGraphicsView>
#include <QApplication>
#include <QScrollBar>
#include <QUndoStack>
#include <QPainter>
#include <QDebug>
#include "commands.h"

Scene::Scene() :
    m_wire(0),
    m_undoStack(new QUndoStack),
    m_modified(false)
{
    setGridSize(15);
    setShowGrid(true);
    setSnapToGrid(true);

    connect(m_undoStack, SIGNAL(canRedoChanged(bool)), SIGNAL(canRedoChanged(bool)));
    connect(m_undoStack, SIGNAL(canUndoChanged(bool)), SIGNAL(canUndoChanged(bool)));
    connect(m_undoStack, SIGNAL(cleanChanged(bool)), SLOT(setModified(bool)));
}

Scene::~Scene()
{
    delete m_undoStack;
    m_undoStack = 0;
}

QList<ComponentItem*> Scene::selectedComponents()
{
    QList<ComponentItem*> components;

    foreach(QGraphicsItem *item, selectedItems()) {
        if(item->type() == Wire::Type)
            continue;

        if(ComponentItem *component = dynamic_cast<ComponentItem*>(item))
            components << component;
    }

    return components;
}

QList<Wire*> Scene::selectedWires()
{
    QList<Wire*> wires;

    foreach(QGraphicsItem *item, selectedItems()) {
        if(Wire *wire = dynamic_cast<Wire*>(item))
            wires << wire;
    }

    return wires;
}

ComponentItem *Scene::selectedComponent()
{
    QList<ComponentItem*> components = selectedComponents();
    if(!components.count())
        return 0;

    return components.first();
}

bool Scene::showGrid() const
{
    return property("showGrid").toBool();
}

bool Scene::snapToGrid() const
{
    return property("snapToGrid").toBool();
}

int Scene::gridSize() const
{
    return property("gridSize").toInt();
}

void Scene::setModified(bool modified)
{
    if(m_modified == modified)
        return;

    if(!modified)
        m_undoStack->setClean();

    m_modified = modified;
    emit modificationChanged(m_modified);
}

bool Scene::canUndo() const
{
    return m_undoStack->canUndo();
}

bool Scene::canRedo() const
{
    return m_undoStack->canRedo();
}

void Scene::deleteSelection()
{
    /*foreach(Wire *wire, selectedWires()) {
        removeItem(wire);
        delete wire;
    }*/

    /*foreach(ComponentItem *component, selectedComponents()) {
        removeItem(component);
        delete component;
    }*/
    m_undoStack->push(new DeleteCommand(this, selectedComponents()));
}

void Scene::showProperties()
{
    if(ComponentItem *item = selectedComponent()) {
        item->showProperties();
    }
}

void Scene::clear()
{
    m_undoStack->clear();

    QGraphicsScene::clear();
}

void Scene::setShowGrid(bool value)
{
    setProperty("showGrid", value);
    update();
}

void Scene::setSnapToGrid(bool value)
{
    setProperty("snapToGrid", value);
}

void Scene::setGridSize(const int &size)
{
    setProperty("gridSize", size);
}

void Scene::alignLeft()
{
    if(selectedComponents().count() < 2)
        return;

    m_undoStack->push(new AlignCommand(selectedComponents(), Qt::AlignLeft));
}

void Scene::alignCenter()
{
    if(selectedComponents().count() < 2)
        return;

    m_undoStack->push(new AlignCommand(selectedComponents(), Qt::AlignHCenter));
}

void Scene::alignRight()
{
    if(selectedComponents().count() < 2)
        return;

    m_undoStack->push(new AlignCommand(selectedComponents(), Qt::AlignRight));
}

void Scene::alignTop()
{
    if(selectedComponents().count() < 2)
        return;

    m_undoStack->push(new AlignCommand(selectedComponents(), Qt::AlignTop));
}

void Scene::alignMiddle()
{
    if(selectedComponents().count() < 2)
        return;

    m_undoStack->push(new AlignCommand(selectedComponents(), Qt::AlignVCenter));
}

void Scene::alignBottom()
{
    if(selectedComponents().count() < 2)
        return;

    m_undoStack->push(new AlignCommand(selectedComponents(), Qt::AlignBottom));
}

void Scene::rotateClockwise()
{
    m_undoStack->push(new RotateCommand(selectedComponents(), 90));
}

void Scene::rotateAnticlockwise()
{
    m_undoStack->push(new RotateCommand(selectedComponents(), -90));
}

void Scene::flipVertical()
{
    m_undoStack->push(new FlipCommand(selectedComponents(), Qt::Vertical));
}

void Scene::flipHorizontal()
{
    m_undoStack->push(new FlipCommand(selectedComponents(), Qt::Horizontal));
}

void Scene::undo()
{
    m_undoStack->undo();
}

void Scene::redo()
{
    m_undoStack->redo();
}

inline float nearestStep(const float &val, const int &step) {
    int tmp = qRound(val) + step / 2;
    tmp -= tmp % step;
    return tmp;
}

void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(!showGrid())
        return;

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setWorldMatrixEnabled(true);

    const int step = gridSize();
    painter->setPen(QPen(QColor(200, 200, 255, 125)));

    float start = nearestStep(rect.top(), step);
    if(start > rect.top()) {
        start -= step;
    }

    for(float y = 0; y < rect.bottom(); y += step) {
        painter->drawLine(rect.left(), y, rect.right(), y);
    }

    start = nearestStep(rect.left(), step);
    if(start > rect.left()) {
        start -= step;
    }

    for(float x = start - step; x < rect.right(); x += step) {
        painter->drawLine(x, rect.top(), x, rect.bottom());
    }

    painter->restore();
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    if(event->buttons() & Qt::LeftButton) {
        foreach(QGraphicsItem *pressItem, items(event->scenePos())) {
            InputPin *input = dynamic_cast<InputPin*>(pressItem);
            OutputPin *output = dynamic_cast<OutputPin*>(pressItem);

            if(!input && !output)
                continue;

            if(input && input->wire())
                continue;

            const QPointF center = pressItem->scenePos() + pressItem->boundingRect().center();
            m_wire = new Wire(center, event->scenePos());
            addItem(m_wire);

            break;
        }
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    if(event->buttons() & Qt::LeftButton) {
        if(!m_wire)
            return;

        m_wire->setEndPos(event->scenePos());
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);

    //TODO
    if(m_wire) {
        const QPointF startPos = m_wire->startPos();
        const QPointF endPos = m_wire->endPos();

        removeItem(m_wire);
        delete m_wire;
        m_wire = 0;

        //start item
        QGraphicsItem *startItem = 0;
        foreach(QGraphicsItem *item, items(startPos)) {
            if((item->type() != InputPin::Type) && (item->type() != OutputPin::Type))
                continue;

            startItem = item;
            break;
        }

        if(!startItem)
            return;

        //end item
        QGraphicsItem *endItem = 0;
        foreach(QGraphicsItem *item, items(endPos)) {
            if((item->type() != InputPin::Type) && (item->type() != OutputPin::Type))
                continue;

            if(item->type() == startItem->type())
                continue;

            endItem = item;
            break;
        }

        if(!endItem)
            return;

        //resolve types
        OutputPin *output = (startItem->type() == OutputPin::Type) ? dynamic_cast<OutputPin*>(startItem) : dynamic_cast<OutputPin*>(endItem);
        InputPin *input   = (startItem->type() == InputPin::Type)  ? dynamic_cast<InputPin*>(startItem)  : dynamic_cast<InputPin*>(endItem);

        if(input->wire())
            return;

        Wire *wire = new Wire(input, output);
        wire->setZValue(-1);
        addItem(wire);
    }
}

void Scene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    const ComponentMimeData *mimeData = qobject_cast<const ComponentMimeData*>(event->mimeData());
    if(!mimeData)
        return;

    Component *component = mimeData->component();
    ComponentItem *dragItem = component->item();

    const QRectF boundingRect = dragItem->boundingRect();
    QPoint targetPos = (event->scenePos() - boundingRect.center()).toPoint();

    if(snapToGrid()) {
        targetPos.setX(targetPos.x() - (targetPos.x() % gridSize()));
        targetPos.setY(targetPos.y() - (targetPos.y() % gridSize()));
    }

    dragItem->setPos(targetPos);
    dragItem->setTransformOriginPoint(boundingRect.center());

    m_undoStack->push(new AddCommand(this, dragItem));
    setModified(true);
}

void Scene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if(qobject_cast<const ComponentMimeData*>(event->mimeData())) {
        event->acceptProposedAction();
        return;
    }

    QGraphicsScene::dragMoveEvent(event);
}
