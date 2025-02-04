#include <QtPlugin>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include <QVTKOpenGLNativeWidget.h>
#include <QIcon>

class QVTKPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit QVTKPlugin(QObject *parent = nullptr) : QObject(parent), initialized(false) {}

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return initialized; }
    QWidget *createWidget(QWidget *parent) override { return new QVTKOpenGLNativeWidget(parent); }
    QString name() const override { return "QVTKOpenGLNativeWidget"; }
    QString group() const override { return "VTK Widgets"; }
    QString toolTip() const override { return "VTK Rendering Widget"; }
    QString whatsThis() const override { return "A Qt widget for VTK rendering."; }
    QString includeFile() const override { return "<QVTKOpenGLNativeWidget.h>"; }

    // 🔹 FIX: Implement missing virtual function
    QIcon icon() const override { return QIcon(); }  // Returns an empty icon

    void initialize(QDesignerFormEditorInterface *) override { initialized = true; }

private:
    bool initialized;
};

// 🔹 Ensure this line is at the end for MOC processing
#include "qvtkplugin.moc"

