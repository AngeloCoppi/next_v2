#ifndef NEW_NEXT_APP_MANAGER_HEADER
#define NEW_NEXT_APP_MANAGER_HEADER

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


#include "n2interfaces.h"
#include "n2exception.h"



class nnExtHandler
{
    extHandler hook;
    void *unknow;
    char name[128];
public :
    nnExtHandler(const char * _name,extHandler & _hook,void *unkObj)
        :hook(_hook),unknow(unkObj)
    {
        strncpy(name,_name,126);
    }

    inline void doHandler(void )
    {
     if(hook && unknow)
     {
         try{
             hook(unknow);
         }
         catch(...)
         {
             extHandlerException *e = new extHandlerException(name);
             throw(e);
         }
     }
    }
};








class nnAppManager
    :public IAppManager
{

typedef std::map<int, childApps *> listChild;

    listChild childs;
    IConfig *configuration;
    int selected;
    static int UID;
public:
    nnAppManager();
    ~nnAppManager();    
    childApps * createObjects(STRING & conf_file_name);
    bool closeAll(void);
    childApps *activate(int v);
    childApps *active(void);
    bool setExtHandler(childApps *child,const char *_name,extHandler & _hook,void *unkObj);
protected:
    bool clean(void);
    bool createInternalObjects(STRING & conf_file_name, childApps & child);

};





#endif
