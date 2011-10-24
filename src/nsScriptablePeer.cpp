/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
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
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

// ==============================
// ! Scriptability related code !
// ==============================

/////////////////////////////////////////////////////
//
// This file implements the nsScriptablePeer object
// The native methods of this class are supposed to
// be callable from JavaScript
//
#include "plugin.h"

static NS_DEFINE_IID(kIScriptableIID, NS_ISCRIPTABLEGECKOMEDIAPLAYER_IID);
static NS_DEFINE_IID(kIScriptableControlIID, NS_ISCRIPTABLEGECKOMEDIAPLAYERCONTROLS_IID);
static NS_DEFINE_IID(kIClassInfoIID, NS_ICLASSINFO_IID);
static NS_DEFINE_IID(kISupportsIID, NS_ISUPPORTS_IID);

nsScriptablePeer::nsScriptablePeer(nsPluginInstance * aPlugin)
{
    mPlugin = aPlugin;
    mRefCnt = 0;
    mPlugin = NULL;
}

nsScriptablePeer::~nsScriptablePeer()
{
}

void nsScriptablePeer::InitControls(nsControlsScriptablePeer * aControls)
{
    mControls = aControls;
}

// AddRef, Release and QueryInterface are common methods and must 
// be implemented for any interface
NS_IMETHODIMP_(nsrefcnt) nsScriptablePeer::AddRef()
{
    ++mRefCnt;
    return mRefCnt;
}

NS_IMETHODIMP_(nsrefcnt) nsScriptablePeer::Release()
{
    --mRefCnt;
    if (mRefCnt == 0) {
        delete this;
        return 0;
    }
    return mRefCnt;
}

// here nsScriptablePeer should return three interfaces it can be asked for by their iid's
// static casts are necessary to ensure that correct pointer is returned
NS_IMETHODIMP nsScriptablePeer::QueryInterface(const nsIID & aIID, void **aInstancePtr)
{
    if (!aInstancePtr)
        return NS_ERROR_NULL_POINTER;

    if (aIID.Equals(kIScriptableIID)) {
        *aInstancePtr = static_cast < nsIScriptableGeckoMediaPlayer * >(this);
        AddRef();
        return NS_OK;
    }

    if (aIID.Equals(kIClassInfoIID)) {
        *aInstancePtr = static_cast < nsIClassInfo * >(this);
        AddRef();
        return NS_OK;
    }

    if (aIID.Equals(kISupportsIID)) {
        *aInstancePtr =
            static_cast < nsISupports * >(static_cast < nsIScriptableGeckoMediaPlayer * >(this));
        AddRef();
        return NS_OK;
    }

    return NS_NOINTERFACE;
}

void nsScriptablePeer::SetInstance(nsPluginInstance * plugin)
{
    mPlugin = plugin;
}

//
// the following methods will be callable from JavaScript
//

NS_IMETHODIMP nsScriptablePeer::Play(void)
{
    printf("JS Play issued\n");
    mPlugin->Play();
    return NS_OK;
}

/* void PlayAt (in double value); */
NS_IMETHODIMP nsScriptablePeer::PlayAt(double value)
{
    printf("JS Play issued\n");
    // mPlugin->PlayAt(value);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::Pause(void)
{
    printf("JS Pause issued\n");
    mPlugin->Pause();
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::PlayPause(void)
{
    printf("JS playPause issued\n");
    mPlugin->PlayPause();
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::Stop(void)
{
    printf("JS Stop issued\n");
    mPlugin->Stop();
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::Quit(void)
{
    printf("JS Quit issued\n");
    // mPlugin->Quit();
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::DoPlay(void)
{
    printf("JS DoPlay issued\n");
    mPlugin->Play();
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::DoPause(void)
{
    printf("JS DoPause issued\n");
    mPlugin->Pause();
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::FastForward(void)
{
    printf("JS FastForward issued\n");
    mPlugin->FastForward();
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::FastReverse(void)
{
    printf("JS FastReverse issued\n");
    mPlugin->FastReverse();
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::Ff(void)
{
    printf("JS ff issued\n");
    mPlugin->FastForward();
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::Rew(void)
{
    printf("JS rew issued\n");
    mPlugin->FastReverse();
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::Rewind(void)
{
    printf("JS Quit issued\n");
    mPlugin->FastReverse();
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::Seek(double counter)
{
    printf("JS Seek issued\n");
    mPlugin->Seek(counter);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetPlayState(PRInt32 * aPlayState)
{
    printf("JS playState issued\n");
    if (mPlugin != NULL) {
        mPlugin->GetPlayState(aPlayState);
    } else {
        *aPlayState = STATE_UNDEFINED;
    }
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetTime(double *_retval)
{
    printf("JS getTime issued\n");
    mPlugin->GetTime(_retval);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetDuration(double *_retval)
{
    printf("JS getDuration issued\n");
    mPlugin->GetDuration(_retval);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetPercent(double *_retval)
{
    printf("JS getPercent issued\n");
    mPlugin->GetPercent(_retval);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetFilename(char **aFilename)
{
    printf("JS filename issued\n");
    mPlugin->GetFilename(aFilename);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SetFilename(const char *aFilename)
{
    printf("JS filename issued\n");
    mPlugin->SetFilename(aFilename);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetSrc(char **aSrc)
{
    printf("JS src requested\n");
    mPlugin->GetFilename(aSrc);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SetSrc(const char *aSrc)
{
    printf("JS src issued to %s\n",aSrc);
    mPlugin->SetFilename(aSrc);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::Open(const char *filename)
{
    printf("JS filename issued\n");
    mPlugin->SetFilename(filename);
    return NS_OK;
}

/* void SetVolume (in double value); */
NS_IMETHODIMP nsScriptablePeer::SetVolume(double value)
{
    printf("JS SetVolume issued\n");
    mPlugin->SetVolume(value);
    return NS_OK;
}

/* double GetVolume (); */
NS_IMETHODIMP nsScriptablePeer::GetVolume(double *_retval)
{
    printf("JS GetVolume issued\n");
    mPlugin->GetVolume(_retval);
    return NS_OK;
}


NS_IMETHODIMP nsScriptablePeer::SetFileName(const char *filename)
{
    printf("JS filename issued\n");
    mPlugin->SetFilename(filename);
    return NS_OK;
}

/* void SetIsLooping (in boolean loop); */
NS_IMETHODIMP nsScriptablePeer::SetIsLooping(PRBool loop)
{
    printf("JS SetIsLooping issued\n");
    mPlugin->SetLoop(loop);
    return NS_OK;
}

/* boolean GetIsLooping (); */
NS_IMETHODIMP nsScriptablePeer::GetIsLooping(PRBool * _retval)
{
    printf("JS GetIsLooping issued\n");
    mPlugin->GetLoop(_retval);
    return NS_OK;
}

/* void SetAutoPlay (in boolean autoPlay); */
NS_IMETHODIMP nsScriptablePeer::SetAutoPlay(PRBool autoPlay)
{
    printf("JS SetAutoPlay issued\n");
    // mPlugin->SetAutoPlay(autoPlay);
    return NS_OK;
}

/* boolean GetAutoPlay (); */
NS_IMETHODIMP nsScriptablePeer::GetAutoPlay(PRBool * _retval)
{
    printf("JS GetAutoPlay issued\n");
    // mPlugin->GetAutoPlay(_retval);
    return NS_OK;
}

  /* boolean isplaying (); */
NS_IMETHODIMP nsScriptablePeer::Isplaying(PRBool * _retval)
{
    printf("JS isplaying issued\n");
    // mPlugin->GetPlaying(_retval);
    return NS_OK;
}

/* void playlistAppend (in string filename); */
NS_IMETHODIMP nsScriptablePeer::PlaylistAppend(const char *item)
{
    printf("JS playlistAppend issued\n");
    // mPlugin->PlaylistAppend(item);
    return NS_OK;
}

/* void playlistClear (PRInt32 *_retval; */
NS_IMETHODIMP nsScriptablePeer::PlaylistClear(PRBool * _retval)
{
    printf("JS playlistClear issued\n");
    // mPlugin->PlaylistClear(_retval);
    return NS_OK;
}


/* void SetHREF (in string url); */
NS_IMETHODIMP nsScriptablePeer::SetHREF(const char *url)
{
    printf("JS filename issued\n");
    mPlugin->SetFilename(url);
    return NS_OK;
}

/* string GetHREF (); */
NS_IMETHODIMP nsScriptablePeer::GetHREF(char **_retval)
{
    printf("JS filename issued\n");
    mPlugin->GetFilename(_retval);
    return NS_OK;
}

/* void SetURL (in string url); */
NS_IMETHODIMP nsScriptablePeer::SetURL(const char *url)
{
    printf("JS filename issued\n");
    mPlugin->SetFilename(url);
    return NS_OK;
}

/* string GetURL (); */
NS_IMETHODIMP nsScriptablePeer::GetURL(char **_retval)
{
    printf("JS filename issued\n");
    mPlugin->GetFilename(_retval);
    return NS_OK;
}

/* string GetMIMEType (); */
NS_IMETHODIMP nsScriptablePeer::GetMIMEType(char **_retval)
{
    printf("JS GetMIMEType issued\n");
    mPlugin->GetMIMEType(_retval);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetShowControls(PRBool * aShowControls)
{
    printf("JS GetShowControls issued\n");
    mPlugin->GetShowControls(aShowControls);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SetShowControls(PRBool aShowControls)
{
    printf("JS SetShowControls issued\n");
    mPlugin->SetShowControls(aShowControls);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetFullscreen(PRBool * aFullscreen)
{
    printf("JS GetFullscreen issued\n");
    mPlugin->GetFullScreen(aFullscreen);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SetFullscreen(PRBool aFullscreen)
{
    printf("JS SetFullscreen issued\n");
    mPlugin->SetFullScreen(aFullscreen);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetShowlogo(PRBool * aShowlogo)
{
    printf("JS GetShowlogo issued\n");
    // mPlugin->GetShowlogo(aShowlogo);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SetShowlogo(PRBool aShowlogo)
{
    printf("JS SetShowlogo issued\n");
    // mPlugin->SetShowlogo(aShowlogo);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::OnClick(const char *event)
{
    mPlugin->SetOnClick(event);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::OnMediaComplete(const char *event)
{
    mPlugin->SetOnMediaComplete(event);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::OnMouseUp(const char *event)
{
    mPlugin->SetOnMouseUp(event);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::OnMouseDown(const char *event)
{
    mPlugin->SetOnMouseDown(event);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::OnMouseOut(const char *event)
{
    mPlugin->SetOnMouseOut(event);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::OnMouseOver(const char *event)
{
    mPlugin->SetOnMouseOver(event);
    return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::OnDestroy(const char *event)
{
    mPlugin->SetOnDestroy(event);
    return NS_OK;
}

// WMP Controls subset

NS_IMETHODIMP nsScriptablePeer::GetControls(nsIScriptableGeckoMediaPlayerControls * *aControls)
{
    *aControls = mControls;
    if (mControls == NULL)
        return NS_ERROR_NULL_POINTER;
    else
        return NS_OK;
}


nsControlsScriptablePeer::nsControlsScriptablePeer(nsPluginInstance * aPlugin)
{
    mPlugin = aPlugin;
    mRefCnt = 0;
}

nsControlsScriptablePeer::~nsControlsScriptablePeer()
{
    //printf("~nsScriptablePeer called\n");
}

// AddRef, Release and QueryInterface are common methods and must
// be implemented for any interface
NS_IMETHODIMP_(nsrefcnt) nsControlsScriptablePeer::AddRef()
{
    ++mRefCnt;
    return mRefCnt;
}

NS_IMETHODIMP_(nsrefcnt) nsControlsScriptablePeer::Release()
{
    --mRefCnt;
    if (mRefCnt == 0) {
        //delete this;
        return 0;
    }
    return mRefCnt;
}

// here nsScriptablePeer should return three interfaces it can be asked for by their iid's
// static casts are necessary to ensure that correct pointer is returned
NS_IMETHODIMP nsControlsScriptablePeer::QueryInterface(const nsIID & aIID, void **aInstancePtr)
{
    if (!aInstancePtr)
        return NS_ERROR_NULL_POINTER;

    if (aIID.Equals(kIScriptableControlIID)) {
        *aInstancePtr = static_cast < nsIScriptableGeckoMediaPlayerControls *> (this);
        AddRef();
        return NS_OK;
    }
    if (aIID.Equals(kIClassInfoIID)) {
        *aInstancePtr = static_cast < nsIClassInfo *> (this);
        AddRef();
        return NS_OK;
    }

    if (aIID.Equals(kISupportsIID)) {
        *aInstancePtr =static_cast < nsISupports * >
                           ( static_cast < nsIScriptableGeckoMediaPlayerControls *> (this));
        AddRef();
        return NS_OK;
    }

    return NS_NOINTERFACE;
}

void nsControlsScriptablePeer::SetInstance(nsPluginInstance * plugin)
{
    mPlugin = plugin;
}

NS_IMETHODIMP nsControlsScriptablePeer::Play(void)
{
    printf("JS Play issued\n");
    mPlugin->Play();
    return NS_OK;
}

NS_IMETHODIMP nsControlsScriptablePeer::Pause(void)
{
    printf("JS Pause issued\n");
    mPlugin->Pause();
    return NS_OK;
}

NS_IMETHODIMP nsControlsScriptablePeer::Stop(void)
{
    printf("JS Stop issued\n");
    mPlugin->Stop();
    return NS_OK;
}

NS_IMETHODIMP nsControlsScriptablePeer::FastForward(void)
{
    printf("JS ff issued\n");
    mPlugin->FastForward();
    return NS_OK;
}

NS_IMETHODIMP nsControlsScriptablePeer::FastReverse(void)
{
    printf("JS rew issued\n");
    mPlugin->FastReverse();
    return NS_OK;
}

NS_IMETHODIMP nsControlsScriptablePeer::Step(void)
{
    mPlugin->Play();
    mPlugin->Pause();
    return NS_OK;
}

NS_IMETHODIMP nsControlsScriptablePeer::GetCurrentPosition(double *aCurrentPosition)
{
    mPlugin->GetTime(aCurrentPosition);
    return NS_OK;
}

NS_IMETHODIMP nsControlsScriptablePeer::SetCurrentPosition(double aCurrentPosition)
{
    mPlugin->Seek(aCurrentPosition);
    return NS_OK;
}


