// For license of this file, see <project-root-folder>/LICENSE.md.

#ifndef FILESYSTEMSIDEBAR_H
#define FILESYSTEMSIDEBAR_H

#include "src/gui/sidebars/dockwidget.h"

#include <QFileSystemModel>
#include <QListWidget>

class FileSystemSidebarModel : public QFileSystemModel {
  Q_OBJECT

  public:
    explicit FileSystemSidebarModel(QObject* parent = nullptr);
    virtual ~FileSystemSidebarModel() = default;
};

class FavoritesListWidget : public QListWidget {
  Q_OBJECT

  public:
    explicit FavoritesListWidget(QWidget* parent = nullptr);
    virtual ~FavoritesListWidget() = default;

  public slots:
    void loadFileItem(const QString& file_path);

  protected:
    virtual void keyPressEvent(QKeyEvent* event) override;
};

class TextApplication;

class FilesystemSidebar : public DockWidget {
  Q_OBJECT

  public:
    explicit FilesystemSidebar(TextApplication* text_app, QWidget* parent = nullptr);
    virtual ~FilesystemSidebar() = default;

    virtual Qt::DockWidgetArea initialArea() const override;
    virtual bool initiallyVisible() const override;
    virtual int initialWidth() const override;

  private slots:
    void addToFavorites();
    void openFavoriteItem(const QModelIndex& idx);
    void openFileFolder(const QModelIndex& idx);
    void goToParentFolder();

  signals:
    void openFileRequested(const QString& file_path);

  private:
    virtual void load() override;

    void saveFavorites() const;

  private:
    FileSystemSidebarModel* m_fsModel;
    QListView* m_fsView;
    FavoritesListWidget* m_lvFavorites;
};

#endif // FILESYSTEMSIDEBAR_H
