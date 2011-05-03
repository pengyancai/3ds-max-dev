//
// Copyright 2009 Autodesk, Inc.  All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.  
//

#pragma once

#include "resource.h"
#include "../../Shared/Common.h"
#include "../../Shared/FXPlugin.h"

//============================================================
// Class descriptor declaration

class TemplateAntiAliasingFilterClassDesc
    : public ClassDesc2 
{
public: 
    //---------------------------------------
    // ClassDesc2 overrides 

    virtual int IsPublic();
    virtual void* Create(BOOL loading = FALSE);
    virtual const MCHAR* ClassName();
    virtual SClass_ID SuperClassID();
    virtual Class_ID ClassID();
    virtual const MCHAR* Category();
    virtual const MCHAR* GetInternalName();
    virtual HINSTANCE HInstance();

    //---------------------------------------
    // Returns a singleton instance of the class descriptor
    static ClassDesc2* GetClassDescInstance();
}; 

//============================================================
// The plug-in definition

class TemplateAntiAliasingFilter 
    : public FXPlugin<FilterKernel>
{
    //============================================================
    // Fields

    // Use member fields only when data is not managed by the parameter block
    // or the reference manager. 
    TODO("Add member fields");

    //============================================================
    // Identifiers for chunks when loading and saving

    TODO("Add your own chunk ids");

    static const int TemplateAntiAliasingFilterHeaderChunkID = 1;

public:
   
    //============================================================
    // Parameter IDs 

    TODO("Replace these with your own parameter IDs");

    static const ParamID FLOAT_PARAM_ID = 0;
    static const ParamID NODE_PARAM_ID = 1;

    //============================================================
    // Constructor/destructor

    TemplateAntiAliasingFilter()
		: FXPlugin<FilterKernel>(TemplateAntiAliasingFilterClassDesc::GetClassDescInstance())
    {         
        TODO("Initialize any member fields");

        // Register references. Note that the parameter block is already registered as a reference 
        // by the PluginBase class
        TODO("Call RegisterReference() for any references you want managed automatically");

        // Register sub-anims. All sub-anims must first be registered as references. Note that the 
        // parameter block is already registered as a reference by the PluginBase class
        TODO("Call RegisterSubAnim() for any managed references which are also sub-animatables");

        // Ask the class descriptor to make the parameter blocks
        // This will trigger 3ds Max to call ReplaceReference with the 
        // constructed parameter block 
        GetClassDesc()->MakeAutoParamBlocks(this);
    }

    ~TemplateAntiAliasingFilter()
    { 
        TODO("Free any memory allocated here");
    }

    //============================================================
    // Animatable overrides 

    IOResult Save(ISave *isave) 
    { 
	    IOResult res;
	    isave->BeginChunk(TemplateAntiAliasingFilterHeaderChunkID);
        
        TODO("Save any member fields");

        res = FXPlugin<FilterKernel>::Save(isave);
	    if (res != IO_OK) return res;
	    isave->EndChunk();
	    return IO_OK;
	}	

    IOResult Load(ILoad *iload) 
    { 
	    IOResult res = IO_OK;
	    
        while (iload->OpenChunk() == IO_OK) 
        {
            int id = iload->CurChunkID();
		    switch(id)  
            {
			    case TemplateAntiAliasingFilterHeaderChunkID:
        
                    TODO("Load any member fields");

                    res = FXPlugin<FilterKernel>::Load(iload);
				    break;
			}
		    iload->CloseChunk();
		
            if (res != IO_OK) 
			    return res;
		}        

	    return IO_OK;
	}

    //============================================================
    // RefMaker overrides 

    // Do not call this function directly, it is for use by 3ds Max
    // If you wish to clone a plug-in you should use CloneRefHierarchy()
    virtual RefTargetHandle Clone(RemapDir& remap) 
    {
        ReferenceTarget* r = new TemplateAntiAliasingFilter();
        BaseClone(this, r, remap);
        return r;
    }

    // Called automatically by SafeClone()
    virtual void BaseClone(ReferenceTarget* from, ReferenceTarget* to, RemapDir& remap)  
    {
        // Don't copy to or from a NULL pointer
        // and don't copy of the source and destination is the same
        if (!from || !to || from == to)
            return;

        // Cast to the correct types
        TemplateAntiAliasingFilter* source = dynamic_cast<TemplateAntiAliasingFilter*>(from);
        TemplateAntiAliasingFilter* target = dynamic_cast<TemplateAntiAliasingFilter*>(to);
        
        DbgAssert(source != NULL && "The source is not the expected type");
        DbgAssert(target != NULL && "The target is not the expected type");

        // Note: the reference manager automatically clones all references for us
        TODO("Copy any data fields from the source to the target");
                
        FXPlugin<FilterKernel>::BaseClone(from, to, remap);
    }

    //=========================================================================
    // FXPlugin<FilterKernel> overrides 

    virtual double KernelFn (double x, double y=0.0)
    {
        TODO("Return the weight of the filtering curve at the specified distance from the center pole of the curve");
        return 0.0;
    }
    virtual long GetKernelSupport()
    {
        TODO("Return an integer number of pixels from center to filter 0 edge, without truncating x dimension for 2D filters");
        return 0;
    }
    virtual long GetKernelSupportY()
    {
        TODO("Return the Y support, if two dimensions are supported, zero otherwise");
        return 0;
    }
    virtual bool Is2DKernel()
    {   
        TODO("Return true if you support is provided for two dimensions");
        return false;
    }
    virtual bool IsVariableSz()
    {
        TODO("Return true if variable size is supported");
        return false;
    }
    virtual void SetKernelSz (double x, double y=0.0)
    {
        TODO("Store the kernel size if supported");
    }
    virtual void GetKernelSz(double &x, double &y)
    {
        TODO("Return the kernel size if supported");
    }
    virtual bool HasNegativeLobes()
    {
        // Currently unused
        return true;
    }
    virtual MCHAR* GetDefaultComment ()
    {
        TODO("Return a string describing the kernel plug-in for the UI");
        // The const_cast is necessary for dealing with bugs.
        return const_cast<MCHAR*>(GetClassDesc()->ClassName());
    }

    //=========================================================================
    // AnimatablePlugin overrides

    virtual ClassDesc2* GetClassDesc()
    {
        return TemplateAntiAliasingFilterClassDesc::GetClassDescInstance();
    }

    //=========================================================================
    // Utility functions for accessing and settting the parameters. 

    TODO("Replace these with your own functions for accessing and setting any parameters");

    void SetFloat(float x, TimeValue t = Now()) 
    {
        SetParameter(FLOAT_PARAM_ID, x, t);
    }

    float GetFloat(TimeValue t = Now()) 
    {
        return GetParameter<float>(FLOAT_PARAM_ID, t);
    }

    void SetNode(INode* node, TimeValue t = Now())
    {
        return SetParameter<INode*>(NODE_PARAM_ID, node, t);
    }

    INode* GetNode(TimeValue t = Now())
    {
        return GetParameter<INode*>(NODE_PARAM_ID, t);
    }
};

//======================================================================
