#include "stdio.h"
#include "CPPtester.h"
#include "windows.h"
#include "n2draw.h"


///////////////////// HEADER //////////////////////

class test_n2draw_class
	: public caTester
{
	CA_TEST_SUITE(test_n2draw_class)
	CA_TEST(test_n2draw_class::test1, "verifica set/get pos");
	CA_TEST(test_n2draw_class::test2, "verifica tostring");
	CA_TEST(test_n2draw_class::test3, "verifica et wire");
	CA_TEST(test_n2draw_class::test4, "verifica tostring");
	CA_TEST(test_n2draw_class::test5, "verifica get direction1");
	CA_TEST(test_n2draw_class::test6, "verifica get direction2");
	CA_TEST(test_n2draw_class::test7, "verifica getConnections().front");
	CA_TEST(test_n2draw_class::test8, "verifica connect 1");
	CA_TEST(test_n2draw_class::test9, "verifica connect 2");
	CA_TEST(test_n2draw_class::test10, "verifica connect 3");
	CA_TEST_SUITE_END()
	void setUp(void);
	void tearDown(void);
	void test1(void);
	void test2(void);
	void test3(void);
	void test4(void);
	void test5(void);
	void test6(void);
	void test7(void);
	void test8(void);
	void test9(void);
	void test10(void);
	
};
///////////////////////////////////////////////////

REGISTER_CLASS(test_n2draw_class);

void test_n2draw_class::setUp(void)
{

}

void test_n2draw_class::tearDown(void)
{

}

void test_n2draw_class::test1(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo setXpos,getXpos,SetYpos,GetYpos");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();

	nnObjComponent  v(ObjContext::objWire);
	v.setXpos(10);
	v.setYpos(20);
	CA_ASSERT(v.getContext()==ObjContext::objWire);
	CA_ASSERT(v.getXpos()==(size_t)10);
	CA_ASSERT(v.getYpos()==(size_t)20);
	v.setXpos(20);
	v.setYpos(40);
	CA_ASSERT(v.getXpos()==(size_t)20);
	CA_ASSERT(v.getYpos()==(size_t)40);
}





void test_n2draw_class::test2(void)
{
	_START();
	_INFO("verifica interna alla classe: metodo tostring");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjCoil  v;
	v.setXpos(10);
	v.setXpos(20);
	size_t t = v.toString().size();
	CA_ASSERT(t != 0);
}

void test_n2draw_class::test3(void)
{
	_START();
	_INFO("verifica interrna alla classe : verifica get set wire");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjWire  v(wireHorizzontal);
	v.setXpos(10);
	v.setYpos(20);
	CA_ASSERT(v.getContext()==ObjContext::objWire);
	CA_ASSERT(v.getXpos() == (size_t)10);
	CA_ASSERT(v.getYpos() == (size_t)20);
	v.setXpos(20);
	v.setYpos(40);
	CA_ASSERT(v.getXpos() == (size_t)20);
	CA_ASSERT(v.getYpos() == (size_t)40);
	CA_ASSERT(v.getWire() == eWire::wireHorizzontal);
	v.setWire(eWire::wireVertical);
	CA_ASSERT(v.getWire() == eWire::wireVertical);
	
}

void test_n2draw_class::test4(void)
{
	_START();
	_INFO("verifica interrna alla classe : struttura tostring");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjWire  v(eWire::wireCross);
	v.setXpos(10);
	v.setXpos(20);
	size_t t = v.toString().size();
	CA_ASSERT(t!=(size_t)0);
	
}

void test_n2draw_class::test5(void)
{
	_START();
	_INFO("verifica interrna alla classe : metodi getdirection");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjWire  v(eWire::wireVertical);
	v.setXpos(10);
	v.setYpos(20);
	nnObjWire  u(eWire::wireVertical);
	u.setXpos(10);
	u.setYpos(5);
	eWireDirection w = u.getDirection(&v);
	CA_ASSERT((size_t)w == (size_t)wire_from_down);
	w = v.getDirection(&u);
	CA_ASSERT((size_t)w == (size_t)wire_from_up);

}

void test_n2draw_class::test6(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo getdirection");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjWire  v(eWire::wireHorizzontal);
	v.setXpos(10);
	v.setYpos(10);
	nnObjWire  u(eWire::wireHorizzontal);
	u.setXpos(20);
	u.setYpos(10);
	eWireDirection w = u.getDirection(&v);
	CA_ASSERT((size_t)w == (size_t)wire_from_left);
	w = v.getDirection(&u);
	CA_ASSERT((size_t)w == (size_t)wire_from_right);
	
}

void test_n2draw_class::test7(void)
{
	_START();
	_INFO("verifica interrna alla classe : metodo getConnections().front");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjWire  v(eWire::noWire);
	nnObjWire  u(eWire::wireHorizzontal);
	v.setPos(10, 15);
	u.setPos(10, 10);
	u.setConnections(1000);
	eWireDirection w = v.getDirection(&u);
	CA_ASSERT((size_t)w == (size_t)wire_from_up);
	bool res = v.connect(&u);
	CA_ASSERT(res == true);
	res = u.connect(&v);
	CA_ASSERT(res == true);
	CA_ASSERT((size_t)v.getWire() == (size_t)eWire::wireVertical);
	CA_ASSERT((size_t)u.getWire() == (size_t)eWire::wireTHorizDown);
	CA_ASSERT(v.getConnections().front() == (size_t)1000);
}

void test_n2draw_class::test8(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo connect 1");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjWire  v(eWire::noWire);
	nnObjWire  u(eWire::wireVertical);
	v.setPos(10, 15);
	u.setPos(10, 10);
	u.setConnections(1000);
	eWireDirection w = v.getDirection(&u);
	CA_ASSERT((size_t)w == (size_t)wire_from_up);
	bool res = v.connect(&u);
	CA_ASSERT(res == true);
	res = u.connect(&v);
	CA_ASSERT(res == true);
	CA_ASSERT((size_t)v.getWire() == (size_t)eWire::wireVertical);
	CA_ASSERT((size_t)u.getWire() == (size_t)eWire::wireVertical);
	CA_ASSERT(v.getConnections().front() == (size_t)1000);
}

void test_n2draw_class::test9(void)
{
	_START();
	_INFO("verifica interrna alla classe:metodo connect 2");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjWire  v(eWire::noWire);
	nnObjWire  u(eWire::wireAngleUpRight);
	v.setPos(10, 15);
	u.setPos(10, 10);
	u.setConnections(1000);
	eWireDirection w = v.getDirection(&u);
	CA_ASSERT((size_t)w == (size_t)wire_from_up);
	bool res = v.connect(&u);
	CA_ASSERT(res==true);
	res = u.connect(&v);
	CA_ASSERT(res == true);
	CA_ASSERT((size_t)v.getWire() == (size_t)eWire::wireVertical);
	CA_ASSERT((size_t)u.getWire() == (size_t)eWire::wireTVertRight);
	CA_ASSERT(v.getConnections().front() == (size_t)1000);
	
}

void test_n2draw_class::test10(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo connect 3");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjWire  v(eWire::noWire);
	nnObjWire  u(eWire::wireAngleUpLeft);
	u.setConnections(1000);
	v.setPos(10, 15);
	u.setPos(10, 10);
	eWireDirection w = v.getDirection(&u);
	CA_ASSERT((size_t)w == (size_t)wire_from_up);
	bool res = v.connect(&u);
	CA_ASSERT(res == true);
	res = u.connect(&v);
	CA_ASSERT(res == true);
	CA_ASSERT((size_t)v.getWire() == (size_t)eWire::wireVertical);
	CA_ASSERT((size_t)u.getWire() == (size_t)eWire::wireTVertLeft);
	CA_ASSERT(v.getConnections().front() == (size_t)1000);
	
}

