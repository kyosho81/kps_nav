
#include <QDebug>

#include "project/project_manage.h"

#include "data_edit_dlg.h"
#include "data_tree.h"

#include "protobuf_msg/state_machine_factory.h"

#include "data_manage_dlg.h"


data_manage_dlg::data_manage_dlg( QWidget *parent) : QSplitter(Qt::Horizontal)
{
	timer_ = 0;
	tree_ = 0;
	model_ = 0;

	data_edit_dlg_ = 0;

// 	btn_refresh_ = 0;
// 	btn_save_ = 0;
// 	btn_add_ = 0 ;
// 	btn_del_ = 0 ;

}

data_manage_dlg::~data_manage_dlg()
{

}

void data_manage_dlg::init_timer()
{
	if (!timer_){
		timer_ = new QTimer(this);
		timer_->setInterval(1000);
		connect(timer_, SIGNAL(timeout()), this, SLOT(updateTimerEvent()));
		timer_->start();
	}else{
		timer_->stop();
		SDelete(timer_);
	}
	
	
}

void data_manage_dlg::updateTimerEvent()
{
//	SM_FACTORY.run_sm();
// 	std::vector<SAGV_Info> v_agv_info;
// 	AGV_MANAGE.do_agv_sm();
// 	AGV_MANAGE.get_agv_status(v_agv_info);
// 	table_->show_agv_list(v_agv_info);
	
}

void data_manage_dlg::init(map_scene* map_sc)
{

	
// 	btn_refresh_ = new QPushButton("refresh");
// 	btn_save_ = new QPushButton("save");
// 
// 
// 	connect(btn_refresh_, SIGNAL(clicked(bool)), this, SLOT(ChooseRefresh(bool)));
// 	connect(btn_save_, SIGNAL(clicked(bool)), this, SLOT(ChooseSave(bool)));


	init_tree_header();
	load_tree_data();

	data_edit_dlg_ = new data_edit_dlg(this);
	data_edit_dlg_->init(map_sc);

	tree_->init(data_edit_dlg_,map_sc);

	addWidget(tree_);
	addWidget(data_edit_dlg_);
	
	init_timer();
}

void data_manage_dlg::ChooseRefresh(bool flag)
{
	load_tree_data();
}

void data_manage_dlg::ChooseSave(bool flag)
{
	//init_timer();
	//SM_FACTORY.init();
}


void data_manage_dlg::init_tree_header()
{
	//1，构造Model，这里示例具有3层关系的model构造过程
	model_ = new QStandardItemModel(this);

	model_->setHorizontalHeaderLabels(QStringList()<<"type");     //设置列头

	//2，给QTreeView应用model
	tree_ = new data_tree;
	tree_->setModel(model_);

	
}

void data_manage_dlg::load_tree_data(){
	model_->clear();
	model_->setHorizontalHeaderLabels(QStringList()<<"type" );     //设置列头
	//load node
	load_node();
	load_edge();
	load_reflector();
	load_lab();
	load_range();
	load_cargo_type();
	load_pallet_type();
	load_producer();
	load_consumer();
	load_processer();
	load_storage();
	load_charge();
	load_rect();
	load_qrcode();
#if 0
	for(int i=0;i<5;i++)
	{
		//一级节点，加入mModel
		
		QStandardItem* item1 = new QStandardItem(QString::number(i));
		QStandardItem* item2 = new QStandardItem("1level");
		QStandardItem* item12 = new QStandardItem("des");
		items1.append(item1);
		items1.append(item2);
		items1.append(item12);
		model_->appendRow(items1);

		for(int j=0;j<5;j++)
		{
			//二级节点,加入第1个一级节点
			QList<QStandardItem*> items2;
			QStandardItem* item3 = new QStandardItem(QString::number(j));
			QStandardItem* item4 = new QStandardItem("2level");
			items2.append(item3);
			items2.append(item4);
			item1->appendRow(items2);

			for(int k=0;k<5;k++)
			{
				//三级节点,加入第1个二级节点
				QList<QStandardItem*> items3;
				QStandardItem* item5 = new QStandardItem(QString::number(k));
				QStandardItem* item6 = new QStandardItem("3level");
				items3.append(item5);
				items3.append(item6);
				item3->appendRow(items3);
			}
		}
	}

	

#endif
	//model_->appendRow(type_list_);
}

void data_manage_dlg::load_node()
{
	item_node_ = new QStandardItem("node");
	
	

	protobuf_node* p_node = 0;
	p_node = PRO_MANAGE.get_next_node("",-1);

	while(p_node){
		

 		QStandardItem* item_id = new QStandardItem( QString(merge_type_id("node",p_node->get_id())));

		item_node_->appendRow(item_id);

		p_node = PRO_MANAGE.get_next_node("",p_node->get_id());

	}
	
	model_->appendRow(item_node_);
	
}

void data_manage_dlg::load_edge()
{
	item_edge_ = new QStandardItem("edge");

	//show edge
	protobuf_edge* p_edge = 0;
	p_edge = PRO_MANAGE.get_next_edge("",-1);

	while(p_edge){

		QStandardItem* item_id = new QStandardItem(QString(merge_type_id("edge",p_edge->get_id())));

		item_edge_->appendRow(item_id);

		p_edge = PRO_MANAGE.get_next_edge("",p_edge->get_id());
	}

	
	model_->appendRow(item_edge_);
}

void data_manage_dlg::load_reflector()
{
	item_reflector_ = new QStandardItem("reflector");


	std::vector<protobuf_reflector*> reflector_list;
	PRO_MANAGE.get_reflector("",reflector_list);
	std::vector<protobuf_reflector*>::iterator it = reflector_list.begin();
	for ( ; it !=  reflector_list.end() ; ++it)
	{
		F32 fx = 0;
		F32 fy = 0;
		(*it)->get_pos(fx,fy);

		QStandardItem* item_id = new QStandardItem( QString( merge_type_id("reflector",(*it)->get_id() )) );

		item_reflector_->appendRow(item_id);
		//lab_item* p_lab_item = item_->get_new_lab_item(fx,fy);

	}

	model_->appendRow(item_reflector_);
	
}

void data_manage_dlg::load_lab()
{

	item_lab_ = new QStandardItem("lab");

	protobuf_lab* p_lab = 0;
	p_lab = Singleton_Project_Manage::get_mutable_instance().get_next_lab("",-1);

	while(p_lab){

		SVec vp;
		p_lab->get_pos(vp.x_,vp.y_);


// 		lab_item* p_item_lab = item_->get_new_lab_item(vp.x_,vp.y_);
// 		p_item_lab->set_id(p_lab->get_id());
// 		p_item_lab->set_lab(p_lab->get_lab());
// 		p_item_lab->setVisible(p_lab->get_show());

		QStandardItem* item_id = new QStandardItem( QString( merge_type_id("lab",p_lab->get_id() )));

		item_lab_->appendRow(item_id);

		p_lab = Singleton_Project_Manage::get_mutable_instance().get_next_lab("",p_lab->get_id());
	}

	model_->appendRow(item_lab_);
}

void data_manage_dlg::load_range()
{
	item_range_ = new QStandardItem("range");

	protobuf_range* p_range = 0;
	p_range = Singleton_Project_Manage::get_mutable_instance().get_next_range("","");

	while(p_range){

		SVec vp;
		SPos pos = p_range->get_start_pos();

		std::vector<Sxy> v_list;
		p_range->get_range(v_list);

// 		range_item*  p_range_item = item_->get_new_range_item(p_range->get_name());
// 		p_range_item->setPos(pos.x_,pos.y_);
// 		p_range_item->add_point(v_list);
		QStandardItem* item_id = new QStandardItem(QString( merge_type_name("range" , p_range->get_name() )));

		item_range_->appendRow(item_id);


		p_range = Singleton_Project_Manage::get_mutable_instance().get_next_range("",p_range->get_name());
	}

	model_->appendRow(item_range_);
}

void data_manage_dlg::load_cargo_type()
{
	item_cargo_type_ = new QStandardItem("cargotype");

	protobuf_cargo_type* p_cargo_type = 0;
	p_cargo_type = PRO_MANAGE.get_next_cargo_type("",-1);

	while(p_cargo_type){

	
		QStandardItem* item_id = new QStandardItem(QString( merge_type_id("cargotype" , p_cargo_type->get_id() )));

		item_cargo_type_->appendRow(item_id);


		p_cargo_type = PRO_MANAGE.get_next_cargo_type("",p_cargo_type->get_id());
	}

	model_->appendRow(item_cargo_type_);
}

void data_manage_dlg::load_pallet_type()
{
	item_pallet_type_ = new QStandardItem("pallettype");

	protobuf_pallet_type* p_pallet_type = 0;
	p_pallet_type = PRO_MANAGE.get_next_pallet_type("",-1);

	while(p_pallet_type){

	
		QStandardItem* item_id = new QStandardItem(QString( merge_type_id("pallettype" , p_pallet_type->get_id() )));

		item_pallet_type_->appendRow(item_id);


		p_pallet_type =  PRO_MANAGE.get_next_pallet_type("",p_pallet_type->get_id());
	}

	model_->appendRow(item_pallet_type_);
}

void data_manage_dlg::load_producer()
{
	item_producer_ = new QStandardItem("producer");

	protobuf_producer* p_producer = 0;
	p_producer = Singleton_Project_Manage::get_mutable_instance().get_next_producer("",-1);

	while(p_producer){

	

		QStandardItem* item_id = new QStandardItem( QString( merge_type_id("producer",p_producer->get_id() )));

		item_producer_->appendRow(item_id);

		p_producer = Singleton_Project_Manage::get_mutable_instance().get_next_producer("",p_producer->get_id());
	}

	model_->appendRow(item_producer_);
}

void data_manage_dlg::load_consumer()
{
	item_consumer_ = new QStandardItem("consumer");

	protobuf_consumer* p_consumer = 0;
	p_consumer = PRO_MANAGE.get_next_consumer("",-1);

	while(p_consumer){



		QStandardItem* item_id = new QStandardItem( QString( merge_type_id("consumer",p_consumer->get_id() )));

		item_consumer_->appendRow(item_id);

		p_consumer = PRO_MANAGE.get_next_consumer("",p_consumer->get_id());
	}

	model_->appendRow(item_consumer_);
}

QString data_manage_dlg::merge_type_id( std::string str_type, int id )
{

	str_type + TYPE_DELIMITER_ID;
	std::stringstream ss;
	ss<<str_type<<TYPE_DELIMITER_ID<<id;
	
	return QString::fromStdString(ss.str());
}

QString data_manage_dlg::merge_type_name( std::string str_type, std::string str_nm )
{
	str_type + TYPE_DELIMITER_ID;
	std::stringstream ss;
	ss<<str_type<<TYPE_DELIMITER_ID<<str_nm;

	return QString::fromStdString(ss.str());
}

void data_manage_dlg::load_processer()
{
	item_processer_ = new QStandardItem("processer");

	protobuf_processer* p_processer = 0;
	p_processer = PRO_MANAGE.get_next_processer("",-1);

	while(p_processer){



		QStandardItem* item_id = new QStandardItem( QString( merge_type_id("processer",p_processer->get_id() )));

		item_processer_->appendRow(item_id);

		p_processer = PRO_MANAGE.get_next_processer("",p_processer->get_id());
	}

	model_->appendRow(item_processer_);
}


void data_manage_dlg::load_storage()
{
	item_storage_ = new QStandardItem("storage");

	protobuf_storage* p_storage = 0;
	p_storage = PRO_MANAGE.get_next_storage("",-1);

	while(p_storage){



		QStandardItem* item_id = new QStandardItem( QString( merge_type_id("storage",p_storage->get_id() )));

		item_storage_->appendRow(item_id);

		p_storage = PRO_MANAGE.get_next_storage("",p_storage->get_id());
	}

	model_->appendRow(item_storage_);
}


void data_manage_dlg::load_charge()
{
	item_charge_ = new QStandardItem("charge");

	protobuf_station* p_charge = 0;
	p_charge = PRO_MANAGE.get_next_charge("",-1);

	while(p_charge){



		QStandardItem* item_id = new QStandardItem( QString( merge_type_id("charge",p_charge->get_id() )));

		item_charge_->appendRow(item_id);

		p_charge = PRO_MANAGE.get_next_charge("",p_charge->get_id());
	}

	model_->appendRow(item_charge_);
}

void data_manage_dlg::load_rect()
{
	item_rect_ = new QStandardItem("rect");

	protobuf_rect* p_rect = 0;
	p_rect = PRO_MANAGE.get_next_rect("","");

	while(p_rect){



		QStandardItem* item_id = new QStandardItem( QString::fromStdString(p_rect->get_name()) );

		item_rect_->appendRow(item_id);

		p_rect = PRO_MANAGE.get_next_rect("", p_rect->get_name());
	}

	model_->appendRow(item_rect_);
}

void data_manage_dlg::load_qrcode()
{
	item_qrcode_ = new QStandardItem("qrcode");

	protobuf_qrcode* p_qrcode = 0;
	p_qrcode = PRO_MANAGE.get_next_qrcode("",-1);

	while(p_qrcode){

		QStandardItem* item_id = new QStandardItem( QString( merge_type_id("qrcode" , p_qrcode->get_uuid() )) );

		item_qrcode_->appendRow(item_id);

		p_qrcode = PRO_MANAGE.get_next_qrcode("", p_qrcode->get_uuid());
	}

	model_->appendRow(item_qrcode_);
}