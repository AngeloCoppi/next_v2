﻿
#ifndef NEW_NEXT_DRAW_HEADER
#define NEW_NEXT_DRAW_HEADER

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

#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <string.h>
#include <algorithm>




typedef struct tag_nn_point
{
    size_t x;
    size_t y;
    tag_nn_point(size_t _x = 0, size_t _y = 0) :x(_x), y(_y) {}
    inline void operator = (const struct tag_nn_point b)
    {
        x = b.x;
        y = b.y;
    }
    inline bool operator != (const struct tag_nn_point b)
    {
        return (x != b.x) || (y != b.y);
    }
    inline bool operator != (const size_t v)
    {
        return (x != v) || (y != v);
    }
    inline bool  isValid(void)
    {
        return (x != -1 && y != -1);
    }
    inline void set(size_t _x, size_t _y)
    {
        x = _x;
        y = _y;
    }

    tag_nn_point intersect(const tag_nn_point & p)
    {

        tag_nn_point res;
        res.x = x < p.x ? x : p.x;
        res.y = y < p.y ? y : p.y;
        return res;
    }
    friend bool operator<(const tag_nn_point & a, const tag_nn_point & b)
    {
        if (a.x < b.x)
            if (a.y < b.y)
                return true;
        return false;
    }
} nnPoint;



typedef struct tag_nn_rect
{
    nnPoint start;
    nnPoint stop;
    tag_nn_rect(size_t top=-1, size_t left=- 1, size_t down= -1, size_t right= -1)
        :start(top, left), stop(down, right) {}
    tag_nn_rect(const nnPoint& p1, const nnPoint & p2)
        :start(p1), stop(p2) {}
    inline void operator = (const struct tag_nn_rect b)
    {
        start = b.start;
        stop = b.stop;
    }
    inline bool operator != (const struct tag_nn_rect b)
    {
        return (start != b.start) || (stop != b.stop);
    }
    inline bool operator != (const size_t v)
    {
        return (start != v) || (stop != v);
    }
    inline bool  isValid(void)
    {
        return (start.isValid()) && (stop.isValid());
    }
    inline void set(size_t _top, size_t _left, size_t _down, size_t _right)
    {
        start.set(_top, _left);
        stop.set(_down, _right);
    }
    inline void set(const tag_nn_point & p1, const tag_nn_point & p2)
    {
        start=p1;
        stop=p2;
    }
    tag_nn_rect intersect(const tag_nn_rect & b)
    {

        tag_nn_rect res;
        res.start = start.intersect(b.start);
        res.stop = stop.intersect(b.stop);
        return res;
    }	
}nnRect;


enum tag_obj_context
{
    objNone = 0,
    objWire,
    objContact,
    objCoil
};


typedef tag_obj_context ObjContext;


enum tag_wire_direction
{
    //0,0,------N,0
    //  
    //0,N-------N,N
    direction_unknow,
    wire_from_up,
    wire_from_down,
    wire_from_left,
    wire_from_right,
};

typedef tag_wire_direction  eWireDirection;

typedef std::vector<size_t >  eConnections;

class miniXmlNode;

class  InnObj
{
public:
    virtual ObjContext getContext(void) = 0;
    virtual void setContext(ObjContext & c) = 0;
    virtual size_t getXpos(void) = 0;
    virtual size_t getYpos(void) = 0;
    virtual void setXpos(size_t pX) = 0;
    virtual void setYpos(size_t pY) = 0;
    virtual void setPos(size_t pX, size_t pY) = 0;
    virtual const std::wstring toString(void) const = 0;
    virtual eWireDirection getDirection(InnObj * b) = 0;
    virtual eConnections & getConnections(void) = 0;
    virtual void setConnections(size_t  v) = 0;
    virtual bool connect(InnObj* b) = 0;
    virtual bool powerConnect(size_t num) = 0;
    virtual bool disconnect(InnObj* b) = 0;
    virtual bool isComponent(void) = 0;
    virtual void save(miniXmlNode *root) = 0;
    virtual void load(miniXmlNode *root) = 0;
};


class  nnObj
    :public InnObj
{
protected:
    ObjContext v_context;
public:
    nnObj(ObjContext c) { v_context = c; }
    inline ObjContext getContext(void) { return v_context; }
    inline void setContext(ObjContext & c) { v_context = c; }
    const std::wstring toString(void) const;
    virtual void save(miniXmlNode *root);
    virtual void load(miniXmlNode *root);
};


class  nnObjPos
    :public nnObj
{
protected:
    size_t v_Xpos;
    size_t v_Ypos;
public:
    nnObjPos(ObjContext c) :nnObj(c), v_Xpos(0), v_Ypos(0) { }
    inline  size_t getXpos(void) { return v_Xpos; }
    inline  size_t getYpos(void) { return v_Ypos; }
    inline  void setXpos(size_t pX) { v_Xpos = pX; }
    inline  void setYpos(size_t pY) { v_Ypos = pY; }
    inline  void setPos(size_t pX, size_t pY) { v_Xpos = pX; v_Ypos = pY; }
    const  std::wstring toString(void) const;
    virtual void save(miniXmlNode *root);
    virtual void load(miniXmlNode *root);
    eWireDirection getDirection(InnObj * pb);
};

enum tag_wire
{
    noWire = 0,
    wireHorizzontal,
    wireVertical,
    wireAngleUpRight,
    wireAngleUpLeft,
    wireAngleDownRight,
    wireAngleDownLeft,
    wireTHorizDown,
    wireTHorizUp,
    wireTVertRight,
    wireTVertLeft,
    wireCross
};

typedef tag_wire eWire;


class InnWire
{
public:
    virtual eWire getWire(void) = 0;
    virtual void setWire(eWire c) = 0;
};

// wire up !=wire down 
class wireConnectionException
    :public std::runtime_error
{
public:
    eConnections up, down;
    explicit wireConnectionException(eConnections _up, eConnections _down) throw()
        :runtime_error("wireConnectionException"), up(_up), down(_down) {}

};

class positionBusyException
    :public std::runtime_error
{
public:
    size_t x, y;
    explicit positionBusyException(size_t _x, size_t _y) throw()
        :runtime_error("positionBusyException"), x(_x), y(_y) {}
};

class failMemoryException
    :public std::runtime_error
{
public:
    char fun[256];
    int line;
    explicit failMemoryException(const char *funct, int _line) throw()
        :runtime_error("failMemoryException"), line(_line) {
        size_t l = strlen(funct);
        size_t t = l < 255 ? l : 255;
        memcpy(fun, funct, t);
        fun[t] = 0;
    }
};


class wireNoAvaiableConnection
    :public std::runtime_error
{
public:
    explicit wireNoAvaiableConnection(void) throw()
        :runtime_error("wireNoAvaiableConnection") {}
};



template<class T>
inline void marshallObj(T* ptr, const char* f, int l)
{
    if (ptr == nullptr)
    {
        failMemoryException e(f, l);
        throw(e);
    }
}

#if (_MSC_VER < 1900)
#define __func__ __FUNCTION__
#define snprintf  _snprintf
#endif		

#define MEMCHK(type,ptr) marshallObj<type>(ptr,__func__,__LINE__)

typedef enum tag_specialization
{
    contact_generic_unknow = 100000,
    coil_generic_unknow = 200000,
    contact_start_spec = 1000000,
    // add here new input components
    contact_generic_coil_normally_open,
    contact_generic_coil_normally_close,
    // end contact spec
    coil_start_spec = 2000000,
    // add here new input components
    coil_generic,

} spec_obj;



class  nnObjConn
    :public nnObjPos
{
protected:
    eConnections v_num;
    static size_t uid_num;

public:
    nnObjConn(ObjContext c) :nnObjPos(c), v_num(0) {}
    inline eConnections & getConnections(void) { return v_num; }
    virtual inline void setConnections(size_t n) { v_num.push_back(n); }
    const  std::wstring toString(void) const;
    virtual void save(miniXmlNode *root);
    virtual void load(miniXmlNode *root);
    static void resetUI(void) { uid_num = 2; }
    static size_t getUI(void) { return ++uid_num; }
    static void setUI(long u) { uid_num = u; }
    bool powerConnect(size_t num);
    static InnObj * getObjFromIds(spec_obj specific, ObjContext context);

};

class  nnObjWire
    : public nnObjConn
    , public InnWire
{
protected:
    eWire v_wire;
public:
    nnObjWire(eWire c) :nnObjConn(ObjContext::objWire)
        , v_wire(c) {}
    inline eWire getWire(void) { return v_wire; }
    inline virtual void setWire(eWire c) { v_wire = c; }
    const  std::wstring toString(void) const;
    virtual void save(miniXmlNode *root);
    virtual void load(miniXmlNode *root);
    inline bool isComponent(void) { return false; }
    bool connect(InnObj * b);
    bool disconnect(InnObj * b);
    bool connectFromUp(size_t b);
    bool connectFromDown(size_t b);
    void setConnections(size_t n);
protected:

    bool connectFromLeft(size_t b);
    bool connectFromRight(size_t b);

    bool disconnectFromUp(size_t b);
    bool disconnectFromDown(size_t b);
    bool disconnectFromLeft(size_t b);
    bool disconnectFromRight(size_t b);
};




class  nnObjComponent
    :public nnObjConn
{
public:
    nnObjComponent(ObjContext c) : nnObjConn(c) {}
    inline bool isComponent(void) { return true; }
    bool connect(InnObj *b);
    bool disconnect(InnObj *b);
    bool connectFromUp(size_t b);
    bool connectFromDown(size_t b);
protected:
    bool disconnectFromUp(void);
    bool disconnectFromDown(void);
};

typedef std::vector<size_t > eVCPUregister;


#include "MerlinoVCPU.h"


class InnVCPU
{
public:
    virtual eVCPUregister &getVCPUregister(void) = 0;
    virtual void setVCPUregister(eVCPUregister & r) = 0;
    virtual const std::wstring toString(void) const = 0;
    virtual void save(miniXmlNode *root) = 0;
    virtual void load(miniXmlNode *root) = 0;
    virtual void setBaseVCPU(pMerlinoVCPU vcpu) = 0;
    virtual pMerlinoVCPU getBaseVCPU(void) = 0;

};

class nnObjVCPU
    :public InnVCPU
{
    pMerlinoVCPU v_vcpu;
    eVCPUregister v_reg;
public:
    nnObjVCPU() :v_vcpu(nullptr) { v_reg.clear(); }
    inline eVCPUregister &getVCPUregister(void) { return  v_reg; }
    inline void setVCPUregister(eVCPUregister & r) { v_reg.clear(); v_reg = r; }
    const std::wstring toString(void) const;
    void save(miniXmlNode *root);
    void load(miniXmlNode *root);
    virtual void setBaseVCPU(pMerlinoVCPU _vcpu) { v_vcpu = _vcpu; };
    virtual pMerlinoVCPU getBaseVCPU(void) { return v_vcpu; }
};




class  nnObjContact
    : public nnObjComponent
    , public nnObjVCPU
{
    spec_obj v_spec;
public:
    nnObjContact(spec_obj _v = spec_obj::contact_generic_unknow) :
        nnObjComponent(ObjContext::objContact), v_spec(_v) {}
    const  std::wstring toString(void) const;
    virtual void save(miniXmlNode *root);
    virtual void load(miniXmlNode *root);
};


class  nnObjCoil
    : public nnObjComponent
    , public nnObjVCPU
{
    spec_obj v_spec;
public:
    nnObjCoil(spec_obj _v = spec_obj::coil_generic_unknow) :
        nnObjComponent(ObjContext::objCoil), v_spec(_v) {}
    const  std::wstring toString(void) const;
    virtual void save(miniXmlNode *root);
    virtual void load(miniXmlNode *root);
};






#endif
