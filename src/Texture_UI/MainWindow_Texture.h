#ifndef MainWindow_Texture_H
#define MainWindow_Texture_H

#include <QMainWindow>
#include "ui_MainWindow_Texture.h"
#include "Dialog_Database.h"
#include <memory>
#include <vector>
#include <string>
#include <QResizeEvent>
class QListWidgetItem;
class Texture_Label;
class QHBoxLayout;
class Texture_Viewer;
class MiniTexture;
class ShapeList;
class TexSynHandler;
class Canvas_Miniview;
class PolyMesh;
class MainWindow_Texture : public QMainWindow, public Ui::MainWindow_Texture
{
    Q_OBJECT

public:
	MainWindow_Texture(QWidget * parent = 0, Qt::WindowFlags flags = 0);
	~MainWindow_Texture();


	

private:
	void connect_singal();
	void set_up_viewer();
	void shape_list_prepare();
	void resizeEvent(QResizeEvent * event);
public:
	void load_obj(QString);
	void clear_meshes();
private slots:
	void show_data_base();
	void set_texture_dir();
	void set_objs_dir();
	void set_objs_dir_load_all_meshes();

	void images_update(int from);
	void objs_update(int from);
	void objs_update_loaded_mesh(int);

	void set_data_dock();
	void load_obj();
	
	void texture_select(MiniTexture*);
	void item_double_clicked(QListWidgetItem *);
   
	void run_d1_synthesis();
	void run_d0_synthesis();
	void mask_d0_select();
	void mask_d1_select();
	void run_d0_synthesis_all();

	void selec_area(bool);
	void clear_select();
	void operationModeChanged(QAction* act);
	void selected_obj(QPoint, QString);

  std::string apply_d1_displacement();
private:
	void set_up_ui_texture();
	void set_up_ui_objs();
	int m_num_layer_texture_;
	int m_num_each_layer_texture_;

	int m_num_layer_objs_;
	int m_num_each_layer_objs_;


	std::vector<Texture_Label*> m_image_labels_;
	std::vector<Canvas_Miniview*> m_miniviewers_;
	std::vector<QHBoxLayout*> m_horizontal_layouts_textures_;
	std::vector<QHBoxLayout*> m_horizontal_layouts_objs_;

	std::vector<QString>		m_texture_files_;
	std::vector<QString>		m_objs_files_;

	int m_start_num_texture_;
	int m_start_num_objs_;

	Dialog_Database* m_dlg_;
	Texture_Viewer*	 m_viewer_;
	ShapeList* m_shape_list_;

	MiniTexture* m_mini_selected_;
	std::shared_ptr<TexSynHandler> tex_syn_handler;

	std::vector<PolyMesh*> m_meshes_loaded_;

};

#endif