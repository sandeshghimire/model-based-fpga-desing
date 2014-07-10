  // Copyright 2007 The MathWorks, Inc.

function RTW_TraceInfo(aFileLinks, aPrevButton, aNextButton, aPanel) {
  this.fFileLinks = aFileLinks;
  this.fLines = new Array();
  this.fNumLines = new Array();
  this.fFileIdxCache = new Array();
  this.fPrevButton = aPrevButton;
  this.fNextButton = aNextButton;
  this.fPanel = aPanel;
  this.fCurrFileIdx = 0;
  this.fCurrLineIdx = 0;
  this.fCurrCodeNode = null;
  this.getHtmlFileName = function(aIndex) {
    if (aIndex < this.fFileLinks.length) {
      var href = this.fFileLinks[aIndex].href;
      return href.substring(href.lastIndexOf('/')+1);
    }
  }
  this.getSrcFileName = function(aIndex) {
    var name = this.getHtmlFileName(aIndex);
    if (name)
      name = RTW_TraceInfo.toSrcFileName(name);
    return name;
  }
  this.getNumFileLinks = function() {
    return this.fFileLinks.length;
  }
  this.setFileLinkColor = function(aIndex, aColor) {
    var link = this.fFileLinks[aIndex];
    if (link && link.parentNode && link.parentNode.style)
      link.parentNode.style.backgroundColor = aColor;
  }
  this.highlightFileLink = function(aIndex, aColor) {
    for (var i = 0; i < this.fFileLinks.length; ++i) {
      this.setFileLinkColor(i, i == aIndex ? aColor : "");
    }
  }
  this.highlightCurrFileLink = function(aColor) {
    this.highlightFileLink(this.fCurrFileIdx);
  }
  this.highlightLines = function(aCodeNode,aColor) {
    this.fCurrCodeNode = aCodeNode;
    var lines = this.fLines[this.getHtmlFileName(this.fCurrFileIdx)];
    if (lines && aCodeNode) {
      for (var i = 0; i < lines.length; ++i) {
        var lineObj = aCodeNode.childNodes[lines[i]-1];
        if (lineObj)
          lineObj.style.backgroundColor=aColor;
      }
    }
  }
  this.getFileIdx = function(aFile) {
    if (this.fFileIdxCache[aFile] != null)
      return this.fFileIdxCache[aFile];
    for (var i = 0; i < this.fFileLinks.length; ++i) {
      if (this.getHtmlFileName(i) == aFile) {
        this.fFileIdxCache[aFile] = i;
        return i;
      }
    }
    return null;
  }
  this.getCurrFileIdx = function() { return this.fCurrFileIdx; }
  this.setNumHighlightedLines = function(aFileIdx, aNumLines) {
    this.fNumLines[aFileIdx] = aNumLines;
    var parent = this.fFileLinks[aFileIdx].parentNode;
    if (parent && parent.childNodes && parent.childNodes.length > 1 &&
        parent.lastChild.innerHTML != undefined) {
      if (aNumLines > 0)
        parent.lastChild.innerHTML = "&nbsp;("+aNumLines+")";
      else
        parent.lastChild.innerHTML = " ";
    }
  }
  this.getNumLines = function(aFileIdx) {
    return this.fNumLines[aFileIdx] != null ? this.fNumLines[aFileIdx] : 0;
  }
  this.removeHighlighting = function() {
    for (var i = 0; i < this.fFileLinks.length; ++i) {
      this.setFileLinkColor(i, "");
      this.setNumHighlightedLines(i, 0);
    }
    this.highlightLines(this.fCurrCodeNode,"");
    this.fCurrCodeObj = null;
    this.fLines = new Array();
    this.fNumLines = new Array();
    this.fFileIdxCache = new Array();
    this.fPrevButton.disabled = true;
    this.fNextButton.disabled = true;
    this.fPanel.style.display = 'none';
    this.fCurrFileIdx = 0;
    this.fCurrLineIdx = 0;
  }
  this.setCurrent = function(aFileIdx, aLineIdx) {
    this.fCurrFileIdx = aFileIdx;
    var numLines = this.getNumLines(aFileIdx);
    if (!numLines || aLineIdx >= numLines)
      this.fCurrLineIdx = -1;
    else
      this.fCurrLineIdx = aLineIdx;
    if (this.fPrevButton)
      this.fPrevButton.disabled = !this.hasPrev();
    if (this.fNextButton)
      this.fNextButton.disabled = !this.hasNext();
    if (this.fPanel)
      this.fPanel.style.display = 'block';
  }
  this.getPrevFileIdx = function() {
    if (this.fCurrLineIdx > 0)
      return this.fCurrFileIdx;
    for (var i = this.fCurrFileIdx - 1; i >= 0; --i)
      if (this.fNumLines[i] > 0)
        return i;
    return null;
  }
  this.hasPrev = function() {
    return this.getPrevFileIdx() != null;
  }
  this.goPrev = function() {
    var fileIdx = this.getPrevFileIdx();
    if (fileIdx == null)
      return;
    if (fileIdx == this.fCurrFileIdx)
      --this.fCurrLineIdx;
    else {
      this.fCurrFileIdx = fileIdx;
      this.fCurrLineIdx = this.getNumLines(fileIdx) - 1;
    }
    if (this.fPrevButton)
      this.fPrevButton.disabled = !this.hasPrev();
    if (this.fNextButton)
      this.fNextButton.disabled = !this.hasNext();
  }
  this.getNextFileIdx = function() {
    if (this.fCurrLineIdx < this.getNumLines(this.fCurrFileIdx) - 1 && this.getNumLines(this.fCurrFileIdx) > 0)
      return this.fCurrFileIdx;
    for (var i = this.fCurrFileIdx + 1; i < this.getNumFileLinks(); ++i)
      if (this.fNumLines[i] > 0)
        return i;
    return null;
  }
  this.hasNext = function() {
    return this.getNextFileIdx() != null;
  }
  this.goNext = function() {
    var fileIdx = this.getNextFileIdx();
    if (fileIdx == null)
      return;
    if (fileIdx == this.fCurrFileIdx)
      ++this.fCurrLineIdx;
    else {
      this.fCurrFileIdx = fileIdx;
      this.fCurrLineIdx = 0;
    }
    if (this.fNextButton)
      this.fNextButton.disabled = !this.hasNext();
    if (this.fPrevButton)
      this.fPrevButton.disabled = !this.hasPrev();
  }
  this.setLines = function(aFile, aLines) {
    this.fLines[aFile] = aLines;
    var index = this.getFileIdx(aFile);
    if (index != null)
      this.setNumHighlightedLines(index,aLines.length);
  }
  this.getLines = function(aFile) {
    return this.fLines[aFile];
  }
  this.getHRef = function(aFileIdx, aLineIdx, offset) {
    if (offset == undefined)
      offset = 10;
    var file = this.getHtmlFileName(aFileIdx);
    var lines = this.fLines[file];
    if (lines) {
      var line = lines[aLineIdx];
      if (offset > 0)
        line = (line > offset ? line - offset : 1);
      file = file+"#"+line;
    }
    return file;
  }
  this.getCurrentHRef = function(offset) {
    return this.getHRef(this.fCurrFileIdx, this.fCurrLineIdx,offset);
  }
  this.setInitLocation = function(aFile, aLine) {
    var fileIdx = this.getFileIdx(aFile);
    var lineIdx = null;
    if (fileIdx != null) {
      var lines = this.getLines(aFile);
      for (var i = 0; i < lines.length; ++i) {
        if (lines[i] == aLine) {
          lineIdx = i;
          break;
        } 
      }
    }
    if (fileIdx == null || lineIdx == null)
      this.setCurrent(0,-1);
    else
      this.setCurrent(fileIdx,lineIdx);
  }
}


RTW_TraceInfo.getFileLinks = function(docObj) {
  var links;
  if (docObj && docObj.getElementsByName)
    links = docObj.getElementsByName("rtwIdGenFileLinks");
  return links ? links : new Array();
}

RTW_TraceInfo.toSrcFileName = function(aHtmlFileName) {
  aHtmlFileName = aHtmlFileName.replace(/_c.html$/,".c");
  aHtmlFileName = aHtmlFileName.replace(/_h.html$/,".h");
  aHtmlFileName = aHtmlFileName.replace(/_cpp.html$/,".cpp");
  aHtmlFileName = aHtmlFileName.replace(/_hpp.html$/,".hpp");
  aHtmlFileName = aHtmlFileName.replace(/_cc.html$/,".hpp");
  aHtmlFileName = aHtmlFileName.replace(/_vhd.html$/,".vhd");
  aHtmlFileName = aHtmlFileName.replace(/_v.html$/,".v");
  return aHtmlFileName;
}

RTW_TraceInfo.instance = null;

RTW_TraceArgs = function(aLocation) {
  this.fColor = null;
  this.fFontSize = null;
  this.fInitFile = null;
  this.fInitLine = null;
  this.fFiles = new Array();
  this.fLines = new Array();
  this.fMessage = null;
  this.fBlock = null;

  if (aLocation.search || aLocation.hash) {
    var query = null;
    if (aLocation.search)
      query = aLocation.search.substring(1);
    else
      query = aLocation.hash.substring(1);
    var args = query.split('&');
    for (var i = 0; i < args.length; ++i) {
      var arg = args[i];
      var sep = arg.indexOf(':');
      if (sep != -1) {
        var fileLines = arg.split(':');
        var htmlFileName = RTW_TraceArgs.toHtmlFileName(fileLines[0]);
        this.fFiles.push(htmlFileName);
        if (fileLines[1])
          this.fLines.push(fileLines[1].split(','));
      } else {
        sep = arg.indexOf('=');
        if (sep != -1) {
          var cmd = arg.substring(0,sep);
          var opt = arg.substring(sep+1);
          switch (cmd.toLowerCase()) {
            case "color":
              this.fColor = opt;
              break;
            case "fontsize":
              this.fFontSize = opt;
              break;
            case "initfile":
              this.fInitFile = RTW_TraceArgs.toHtmlFileName(opt);
              break;
            case "initline":
              this.fInitLine = opt;
              break;
            case "msg":
              this.fMessage = opt;
              break;
            case "block":
              this.fBlock = unescape(opt);
              break;
          }
        }
      }
    }
    if (this.fInitFile == null) {
      this.fInitFile = this.fFiles[0];
      this.fInitLine = (this.fLines[0] == null ? -1 : this.fLines[0][0]);
    }
  }

  this.getColor = function() { return this.fColor; }
  this.getFontSize = function() { return this.fFontSize; }
  this.getInitFile = function() { return this.fInitFile; }
  this.getInitLine = function() { return this.fInitLine; }
  this.getNumFiles = function() { return this.fFiles.length; }
  this.getFile = function(aIdx) { return this.fFiles[aIdx]; }
  this.getLines = function(aIdx) { return this.fLines[aIdx]; }
}


RTW_TraceArgs.toHtmlFileName = function(aFile) {
  aFile = aFile.replace(/.c$/,"_c.html");
  aFile = aFile.replace(/.h$/,"_h.html");
  aFile = aFile.replace(/.cpp$/,"_cpp.html");
  aFile = aFile.replace(/.hpp$/,"_hpp.html");
  aFile = aFile.replace(/.cc$/,"_cc.html");
  aFile = aFile.replace(/.vhd$/,"_vhd.html");
  aFile = aFile.replace(/.v$/,"_v.html");
  return aFile;
}

RTW_TraceArgs.instance = null;

RTW_MessageWindow = function(aWindow, aParagraph) {
  this.fWindow    = aWindow;
  this.fParagraph = aParagraph;
  
  this.print = function(msg) {
    this.fParagraph.innerHTML = msg;
    if (msg)
      this.fWindow.style.display = "block";
    else
      this.fWindow.style.display = "none";
  }
  this.clear = function() {
    this.print("");
  }
}

RTW_MessageWindowFactory = function(aDocObj) {
  this.fDocObj = aDocObj;
  this.fInstance = null;

  this.getInstance = function() {
    if (this.fInstance)
      return this.fInstance;
    if (!this.fDocObj)
      return;
      
    var table     = this.fDocObj.getElementById("rtwIdMsgWindow");
    var paragraph = this.fDocObj.getElementById("rtwIdMsg");
    var button    = this.fDocObj.getElementById("rtwIdButtonMsg");

    if (!table || !paragraph || !button)
      return null;

    obj = new RTW_MessageWindow(table,paragraph);
    button.onclick = function() { obj.clear(); }
    this.fInstance = obj;
    return this.fInstance;
  }
}

RTW_MessageWindowFactory.instance = null;
RTW_MessageWindow.factory = function(aDocObj) {
  if (!RTW_MessageWindowFactory.instance)
    RTW_MessageWindowFactory.instance = new RTW_MessageWindowFactory(aDocObj);
  return RTW_MessageWindowFactory.instance.getInstance();
}



function rtwSrcFrame() {
  return top.rtwreport_document_frame;
}
function rtwTocFrame() {
  return top.rtwreport_contents_frame;
}

function rtwGetFileName(url) {
  var slashIdx = url.lastIndexOf('/');
  var hashIdx  = url.indexOf('#');
  if (hashIdx == -1)
    return url.substring(slashIdx+1)
  else
    return url.substring(slashIdx+1,hashIdx);
}

function rtwFileOnLoad(winObj) {
  if (!winObj.location || !winObj.location.href || !winObj.document
      || !RTW_TraceInfo.instance)
    return;
  docObj = winObj.document;
  if (!docObj.getElementById)
    return;
  if (rtwSrcFrame())
    rtwSrcFrame().focus();
  var fileName = rtwGetFileName(winObj.location.href);
  var fileIdx = RTW_TraceInfo.instance.getFileIdx(fileName);
  if (fileIdx != null) {
    if (fileIdx != RTW_TraceInfo.instance.getCurrFileIdx())
      RTW_TraceInfo.instance.setCurrent(fileIdx,-1);
    var codeNode = docObj.getElementById("RTWcode");
    var hiliteColor = RTW_TraceArgs.instance.getColor();
    if (!hiliteColor) {
        hiliteColor = "#aaffff";
    }
    var fontSize = RTW_TraceArgs.instance.getFontSize();
    if (fontSize) {
        codeNode.style.fontSize = fontSize;
    }
    RTW_TraceInfo.instance.highlightLines(codeNode,hiliteColor);
    RTW_TraceInfo.instance.highlightFileLink(fileIdx,"#ffff99");
  }
}

function rtwGoPrev() {
  if (RTW_TraceInfo.instance) {
    RTW_TraceInfo.instance.goPrev();
    top.rtwreport_document_frame.document.location.href=RTW_TraceInfo.instance.getCurrentHRef();
  }
}

function rtwGoNext() {
  if (RTW_TraceInfo.instance) {
    RTW_TraceInfo.instance.goNext();
    top.rtwreport_document_frame.document.location.href=RTW_TraceInfo.instance.getCurrentHRef();
  }
}

function rtwMainOnLoadFcn(topDocObj,tocDocObj,fileDocObj,aLoc) {
  var loc;
  if (!aLoc) {
    loc = topDocObj.location;
  } else {
    loc = new Object();
    loc.hash = "#"+aLoc;
  }
    
  RTW_TraceArgs.instance = new RTW_TraceArgs(loc);
  var initPage;
  if (RTW_TraceArgs.instance.getNumFiles()) {
    var fileLinks = RTW_TraceInfo.getFileLinks(tocDocObj);
    var prevButton = tocDocObj.getElementById("rtwIdButtonPrev");
    var nextButton = tocDocObj.getElementById("rtwIdButtonNext");
    var panel = tocDocObj.getElementById("rtwIdTracePanel");
    RTW_TraceInfo.instance = new RTW_TraceInfo(fileLinks, prevButton, nextButton, panel);
    RTW_TraceInfo.instance.removeHighlighting();
    var numFiles = RTW_TraceArgs.instance.getNumFiles();
    for (var i = 0; i < numFiles; ++i) {
      RTW_TraceInfo.instance.setLines(RTW_TraceArgs.instance.getFile(i),RTW_TraceArgs.instance.getLines(i));
    }
    var initFile = RTW_TraceArgs.instance.getInitFile();
    RTW_TraceInfo.instance.setInitLocation(initFile,RTW_TraceArgs.instance.getInitLine());
    initPage = RTW_TraceInfo.instance.getCurrentHRef();
  } else {
    var summaryPage = tocDocObj.getElementById("rtwIdSummaryPage");
    if (summaryPage)
      initPage = summaryPage.href;
  }
  if (RTW_TraceArgs.instance && RTW_TraceArgs.instance.fMessage) {
    var msgFile = tocDocObj.getElementById('rtwIdMsgFileLink');
    if (msgFile && msgFile.style) {
      msgFile.style.display = "block";
    }
    initPage = "rtwmsg.html";
  }
  fileDocObj.location.href = initPage;
}

function rtwMainOnLoad() {
  rtwMainOnLoadFcn(document,top.rtwreport_contents_frame.document,top.rtwreport_document_frame.document,null);
}

function rtwMainReload(location) {
  rtwMainOnLoadFcn(document,top.rtwreport_contents_frame.document,top.rtwreport_document_frame.document,location);
}

function rtwRemoveHighlighting() {
  if (RTW_TraceInfo.instance)
    RTW_TraceInfo.instance.removeHighlighting();
  if (rtwSrcFrame())
    rtwSrcFrame().focus();
}

function rtwDisplayMessage() {
  var docObj = top.rtwreport_document_frame.document;
  var msg = docObj.getElementById(RTW_TraceArgs.instance.fMessage);
  if (!msg) {
    msg = docObj.getElementById("rtwMsg_notTraceable");
  }
  if (msg && msg.style) {
    msg.style.display = "block"; 
    var msgstr = msg.innerHTML;
    if (RTW_TraceArgs.instance.fBlock) {
      msgstr = msgstr.replace("%s",RTW_TraceArgs.instance.fBlock);
    }
    msg.innerHTML = msgstr;
  }
}


  window.onload=rtwMainOnLoad;

