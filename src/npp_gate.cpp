/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: NPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or 
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

////////////////////////////////////////////////////////////
//
// Implementation of plugin entry points (NPP_*)
// most are just empty stubs for this particular plugin 
//
#include "plugin.h"
#include "plugin_types.h"
#include "plugin_setup.h"

char *NPP_GetMIMEDescription(void)
{
    return GetMIMEDescription();
}


NPError NPP_Initialize(void)
{
    return NPERR_NO_ERROR;
}

void NPP_Shutdown(void)
{
}

// here the plugin creates an instance of our CPlugin object which 
// will be associated with this newly created plugin instance and 
// will do all the neccessary job
NPError NPP_New(NPMIMEType pluginType,
                NPP instance,
                uint16_t mode, int16_t argc, char *argn[], char *argv[], NPSavedData * saved)
{
    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;

    NPError rv = NPERR_NO_ERROR;

    printf("NPP_New called\n");
    CPlugin *pPlugin = new CPlugin(instance);
    if (pPlugin == NULL)
        return NPERR_OUT_OF_MEMORY_ERROR;

    instance->pdata = (void *) pPlugin;
    pPlugin->mode = mode;
    pPlugin->mimetype = g_strdup(pluginType);
    pPlugin->mInstance = instance;
    new_instance(pPlugin, argc, argn, argv);
    return rv;
}

// here is the place to clean up and destroy the CPlugin object
NPError NPP_Destroy(NPP instance, NPSavedData ** save)
{
    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;

    NPError rv = NPERR_NO_ERROR;

    CPlugin *pPlugin = (CPlugin *) instance->pdata;
    if (pPlugin != NULL) {
        pPlugin->shut();
        delete pPlugin;
    }
    return rv;
}

// during this call we know when the plugin window is ready or
// is about to be destroyed so we can do some gui specific
// initialization and shutdown
NPError NPP_SetWindow(NPP instance, NPWindow * pNPWindow)
{
    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;

    NPError rv = NPERR_NO_ERROR;

    if (pNPWindow == NULL)
        return NPERR_GENERIC_ERROR;

    CPlugin *pPlugin = (CPlugin *) instance->pdata;

    if (pPlugin == NULL)
        return NPERR_GENERIC_ERROR;

    // window just created
    if (!pPlugin->isInitialized() && (pNPWindow->window != NULL)) {
        if (!pPlugin->init(pNPWindow)) {
            delete pPlugin;
            pPlugin = NULL;
            return NPERR_MODULE_LOAD_FAILED_ERROR;
        }
    }
    // window goes away
    if ((pNPWindow->window == NULL) && pPlugin->isInitialized())
        return NPERR_NO_ERROR;

    // window resized
    if (pPlugin->isInitialized() && (pNPWindow->window != NULL)) {
        printf("Window resized\n");
        pPlugin->SetWindow(pNPWindow);
        return NPERR_NO_ERROR;
    }
    // this should not happen, nothing to do
    if ((pNPWindow->window == NULL) && !pPlugin->isInitialized())
        return NPERR_NO_ERROR;

    return rv;
}

// ==============================
// ! Scriptability related code !
// ==============================
//
// here the plugin is asked by Mozilla to tell if it is scriptable
// we should return a valid interface id and a pointer to 
// nsScriptablePeer interface which we should have implemented
// and which should be defined in the corressponding *.xpt file
// in the bin/components folder
NPError NPP_GetValue(NPP instance, NPPVariable variable, void *value)
{
    NPError rv = NPERR_NO_ERROR;

    if (variable == NPPVpluginScriptableNPObject) {
        if (instance == NULL)
            return NPERR_INVALID_INSTANCE_ERROR;
        CPlugin *plugin = (CPlugin *) instance->pdata;
        if (plugin == NULL)
            return NPERR_GENERIC_ERROR;
        *(NPObject **) value = plugin->GetScriptableObject();
    } else {
        rv = PluginGetValue(variable, value);
    }

    return rv;
}

NPError NPP_NewStream(NPP instance,
                      NPMIMEType type, NPStream * stream, NPBool seekable, uint16_t * stype)
{
    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;

    NPError rv = NPERR_NO_ERROR;

    CPlugin *pPlugin = (CPlugin *) instance->pdata;

    if (pPlugin == NULL)
        return NPERR_GENERIC_ERROR;

    pPlugin->NewStream(type, stream, seekable, stype);

    return rv;
}

int32_t NPP_WriteReady(NPP instance, NPStream * stream)
{
    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;

    int32_t rv = 0x0fffffff;
    CPlugin *pPlugin = (CPlugin *) instance->pdata;

    if (pPlugin == NULL)
        return NPERR_GENERIC_ERROR;

    rv = pPlugin->WriteReady(stream);
    // printf("rv = %i\n",rv);

    return rv;
}

int32_t NPP_Write(NPP instance, NPStream * stream, int32_t offset, int32_t len, void *buffer)
{
    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;

    int32_t rv = len;
    CPlugin *pPlugin = (CPlugin *) instance->pdata;

    if (pPlugin == NULL)
        return NPERR_GENERIC_ERROR;

    rv = pPlugin->Write(stream, offset, len, buffer);
    // printf("rv = %i\n", rv);
    return rv;
}

NPError NPP_DestroyStream(NPP instance, NPStream * stream, NPError reason)
{
    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;

    NPError rv = NPERR_NO_ERROR;
    CPlugin *pPlugin = (CPlugin *) instance->pdata;

    if (pPlugin == NULL)
        return NPERR_GENERIC_ERROR;

    pPlugin->DestroyStream(stream, reason);
    return rv;
}

void NPP_StreamAsFile(NPP instance, NPStream * stream, const char *fname)
{
    if (instance == NULL)
        return;
}

void NPP_Print(NPP instance, NPPrint * printInfo)
{
    if (instance == NULL)
        return;
}

void NPP_URLNotify(NPP instance, const char *url, NPReason reason, void *notifyData)
{
    if (instance == NULL)
        return;

    CPlugin *pPlugin = (CPlugin *) instance->pdata;

    if (pPlugin == NULL)
        return;

    pPlugin->URLNotify(url, reason, notifyData);

}

NPError NPP_SetValue(NPP instance, NPNVariable variable, void *value)
{
    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;

    NPError rv = NPERR_NO_ERROR;
    return rv;
}

int16_t NPP_HandleEvent(NPP instance, void *event)
{
    if (instance == NULL)
        return 0;

    int16_t rv = 0;
    CPlugin *pPlugin = (CPlugin *) instance->pdata;
    if (pPlugin)
        rv = pPlugin->handleEvent(event);

    return rv;
}

/*
jref NPP_GetJavaClass (void)
{
  return NULL;
}
*/

NPObject *NPP_GetScriptableInstance(NPP instance)
{
    if (!instance)
        return 0;

    NPObject *npobj = 0;
    CPlugin *pPlugin = (CPlugin *) instance->pdata;
    if (!pPlugin)
        npobj = pPlugin->GetScriptableObject();

    return npobj;
}
