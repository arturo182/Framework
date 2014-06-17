#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>
#include <QPointF>

class ComponentItem;
class Scene;

class AddCommand : public QUndoCommand
{
    public:
        AddCommand(Scene *scene, ComponentItem *item);

        void undo();
        void redo();

    private:
        Scene *m_scene;
        ComponentItem *m_item;
};

class DeleteCommand : public QUndoCommand
{
    public:
        DeleteCommand(Scene *scene, const QList<ComponentItem*> &items);

        void undo();
        void redo();

    private:
        Scene *m_scene;
        QList<ComponentItem*> m_items;
};

class RotateCommand : public QUndoCommand
{
    public:
        RotateCommand(const QList<ComponentItem*> &items, const double &angle);

        void undo();
        void redo();

    private:
        QList<ComponentItem*> m_items;
        double m_angle;
};

class AlignCommand : public QUndoCommand
{
    public:
        AlignCommand(const QList<ComponentItem*> &items, const Qt::AlignmentFlag &alignment);

        void undo();
        void redo();

    private:
        QList<ComponentItem*> m_items;
        Qt::AlignmentFlag m_alignment;
        QList<QPointF> m_oldPositions;
};

class FlipCommand : public QUndoCommand
{
    public:
        FlipCommand(const QList<ComponentItem*> &items, const Qt::Orientation &orientation);

        void undo();
        void redo();

    private:
        QList<ComponentItem*> m_items;
        Qt::Orientation m_orientation;
};

#endif // COMMANDS_H
