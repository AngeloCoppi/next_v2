#include "stdio.h"
#include "CPPtester.h"
#include "n2draw.h"
#include "n2drawmanager.h"
#include <iostream>
#include "miniXml.h"

/**************************************************************
Copyright(c) 2015 Angelo Coppi

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files(the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions :

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
********************************************************************/

///////////////////// HEADER //////////////////////

class test_n2ObjManager
	: public caTester
{
	CA_TEST_SUITE(test_n2ObjManager)
		CA_TEST(test_n2ObjManager::test1, "verifica set/get pos");
	CA_TEST(test_n2ObjManager::test2, "verifica tostring");
	CA_TEST(test_n2ObjManager::test4, "verifica tostring");
	CA_TEST(test_n2ObjManager::test5, "verifica get direction1");
	CA_TEST(test_n2ObjManager::test6, "verifica get direction2");
	CA_TEST(test_n2ObjManager::test7, "verifica connect/disconnect");
	CA_TEST(test_n2ObjManager::test8, "verifica connect/disconnect");
	CA_TEST(test_n2ObjManager::test9, "verifica connect/disconnect");
	CA_TEST(test_n2ObjManager::test10, "verifica connect/disconnect");
	CA_TEST(test_n2ObjManager::test11, "verifica move");
	CA_TEST(test_n2ObjManager::test12, "verifica save");
	CA_TEST_SUITE_END()
		void setUp(void) {}
	void tearDown(void) {}
	void test1(void);
	void test2(void);

	void test4(void);
	void test5(void);
	void test6(void);
	void test7(void);
	void test8(void);
	void test9(void);
	void test10(void);
	void test11(void);
	void test12(void);
};
///////////////////////////////////////////////////

REGISTER_CLASS(test_n2ObjManager);


void test_n2ObjManager::test1(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo ");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjManager mn(50, 20);
	nnObjWire *v = new nnObjWire(eWire::wireAngleDownLeft);
	bool res = mn.addObj(10, 12, v);
	CA_ASSERT(res == true);
	CA_ASSERT((int)mn.size() == (int)1);
	res = mn.removeAll();
	CA_ASSERT(res == true);
}



void test_n2ObjManager::test2(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo ");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjManager mn(50, 20);
	nnObjWire *v = new nnObjWire(eWire::wireAngleDownLeft);
	bool res = mn.addObj(10, 12, v);
	CA_ASSERT(res == true);
	CA_ASSERT((int)mn.size() == (int)1);
	nnObjComponent *u = new nnObjCoil();
	res = mn.replaceObj(10, 12, u);
	CA_ASSERT(res == true);
	CA_ASSERT((int)mn.size() == (int)1);
	res = mn.removeObj(10, 12);
	CA_ASSERT(res == true);
	CA_ASSERT((int)mn.size() == 0);
	res = mn.removeAll();
	CA_ASSERT(res == false);
}


void test_n2ObjManager::test4(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo ");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjManager mn(50, 20);
	nnObjComponent *c = new nnObjComponent(ObjContext::objContact);
	mn.addObj(5, 0, c);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)0);
	CA_ASSERT(mn.size() == 1);

}

void test_n2ObjManager::test5(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo ");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjManager mn(50, 20);
	nnObjComponent *c = new nnObjComponent(ObjContext::objContact);
	mn.addObj(5, 0, c);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)0);
	InnObj * p = mn.getObj(5, 0);
	std::wstring w = p->toString();
	std::wcout << w.c_str()<<std::endl;
	w = c->toString();
	std::wcout << w.c_str() << std::endl;
}


void test_n2ObjManager::test6(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo ");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjManager mn(50, 20);
	nnObjComponent *c = new nnObjComponent(ObjContext::objContact);
	mn.addObj(5, 0, c);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)0);
	nnObjComponent *d = new nnObjComponent(ObjContext::objContact);
	mn.addObj(5, 1, d);
	InnObj * p = mn.getObj(5, 0);
	std::wstring w = p->toString();
	std::wcout << w.c_str() << std::endl;
	w = c->toString();
	std::wcout << w.c_str() << std::endl;
	w = d->toString();
	std::wcout << w.c_str() << std::endl;
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)3);
	CA_ASSERT(d->getConnections().front() == (size_t)3);
	CA_ASSERT(d->getConnections().back() == (size_t)0);
}

void test_n2ObjManager::test7(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo ");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjManager mn(50, 20);
	nnObjComponent *c = new nnObjComponent(ObjContext::objContact);
	mn.addObj(5, 0, c);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)0);
	nnObjComponent *d = new nnObjComponent(ObjContext::objContact);
	mn.addObj(5, 1, d);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)3);
	CA_ASSERT(d->getConnections().front() == (size_t)3);
	CA_ASSERT(d->getConnections().back() == (size_t)0);
	mn.removeObj(5, 1);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)0);
}


void test_n2ObjManager::test8(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo connect disconnect ");
	_INFO("inserimento 3 contatti serie e rimozione del contatto centrale");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjManager mn(50, 20);
	nnObjComponent *c = new nnObjComponent(ObjContext::objContact);
	mn.addObj(5, 0, c);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)0);
	nnObjComponent *d = new nnObjComponent(ObjContext::objContact);
	mn.addObj(5, 1, d);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)3);
	CA_ASSERT(d->getConnections().front() == (size_t)3);
	CA_ASSERT(d->getConnections().back() == (size_t)0);
	nnObjComponent *e = new nnObjComponent(ObjContext::objContact);
	mn.addObj(5, 2, e);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)3);
	CA_ASSERT(d->getConnections().front() == (size_t)3);
	CA_ASSERT(d->getConnections().back() == (size_t)4);
	CA_ASSERT(e->getConnections().front() == (size_t)4);
	CA_ASSERT(e->getConnections().back() == (size_t)0);
	mn.removeObj(5, 1);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)0);
	CA_ASSERT(e->getConnections().front() == (size_t)0);
	CA_ASSERT(e->getConnections().back() == (size_t)0);
}


void test_n2ObjManager::test9(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo connect disconnect  ");
	_INFO("inserimento 2 contatti serie e rimozione del file centrale");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjManager mn(50, 20);
	nnObjComponent* c = new nnObjComponent(ObjContext::objContact);
	mn.addObj(5, 0, c);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)0);
	nnObjWire *d = new nnObjWire(eWire::noWire);
	mn.addObj(5, 1, d);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)3);
	CA_ASSERT(d->getConnections().front() == (size_t)3);;
	nnObjComponent *e = new nnObjComponent(ObjContext::objContact);
	mn.addObj(5, 2, e);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)3);
	CA_ASSERT(d->getConnections().front() == (size_t)3);
	CA_ASSERT(e->getConnections().front() == (size_t)3);
	CA_ASSERT(e->getConnections().back() == (size_t)0);
	mn.removeObj(5,1);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)0);
	CA_ASSERT(e->getConnections().front() == (size_t)0);
	CA_ASSERT(e->getConnections().back() == (size_t)0);
}

void test_n2ObjManager::test10(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo connect disconnect  ");
	_INFO("inserimento 2 contatti serie e rimozione del file primo centrale");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjManager mn(50, 20);
	nnObjComponent* c = new nnObjComponent(ObjContext::objContact);
	mn.addObj(5, 0, c);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)0);
	nnObjWire *d = new nnObjWire(eWire::noWire);
	mn.addObj(5, 1, d);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)3);
	CA_ASSERT(d->getConnections().front() == (size_t)3);
	nnObjWire *e = new nnObjWire(eWire::noWire);
	mn.addObj(5, 2, e);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)3);
	CA_ASSERT(d->getConnections().front() == (size_t)3);
	CA_ASSERT(e->getConnections().front() == (size_t)3);
	nnObjComponent *f = new nnObjComponent(ObjContext::objContact);
	mn.addObj(5, 3, f);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)3);
	CA_ASSERT(d->getConnections().front() == (size_t)3);
	CA_ASSERT(e->getConnections().front() == (size_t)3);
	CA_ASSERT(f->getConnections().front() == (size_t)3);
	CA_ASSERT(f->getConnections().back() == (size_t)0);
	mn.removeObj(5, 1);
	CA_ASSERT(c->getConnections().front() == (size_t)1);
	CA_ASSERT(c->getConnections().back() == (size_t)0);
	CA_ASSERT(f->getConnections().front() == (size_t)0);
	CA_ASSERT(f->getConnections().back() == (size_t)0);
	CA_ASSERT(mn.size() == 2);
}


void test_n2ObjManager::test11(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo move");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjManager mn(50, 20);
	nnObjCoil *c = new nnObjCoil();
	bool res = mn.addObj(10, 12, c);
	CA_ASSERT(res == true);
	CA_ASSERT((int)mn.size() == (int)1);
	CA_ASSERT(mn.getObj(10, 12) != nullptr);
	CA_ASSERT(mn.getObj(10, 12)->isComponent());
	res = mn.moveObj(n2Point(10, 12), n2Point(5, 3));
	CA_ASSERT(res == true);
	CA_ASSERT((int)mn.size() == (int)1);
	CA_ASSERT(mn.getObj(5, 3) != nullptr);
	CA_ASSERT(mn.getObj(5, 3)->isComponent());
	CA_ASSERT(mn.getObj(10, 12) == nullptr);
	res = mn.removeAll();
	CA_ASSERT(res == true);
}


void test_n2ObjManager::test12(void)
{
	_START();
	_INFO("verifica interrna alla classe: metodo save");
	_AUTHOR("Coppi Angelo n2draw library ");
	_STOP();
	nnObjManager mn(50, 20);
	nnObjCoil *c = new nnObjCoil();
	bool res = mn.addObj(10, 12, c);
	CA_ASSERT(res == true);
	c = new nnObjCoil();
	res = mn.addObj(11, 12, c);
	CA_ASSERT(res == true);
	c = new nnObjCoil();
	res = mn.addObj(12, 12, c);
	CA_ASSERT(res == true);
	nnObjContact *d = new nnObjContact();
	res = mn.addObj(10, 5, d);
	CA_ASSERT(res == true);
	d = new nnObjContact();
	res = mn.addObj(11, 5, d);
	CA_ASSERT(res == true);
	d = new nnObjContact();
	res = mn.addObj(12, 5, d);
	CA_ASSERT(res == true);
	remove(".\\testsave.xml");
	std::string name(".\\testsave.xml");
	mn.save(name);
	miniXmlNode root("",(char*)"");
	root.load(name.c_str(), &root);
	remove(".\\testsave.xml");
	root.print(stdout);
	res = mn.removeAll();
	CA_ASSERT(res == true);
}