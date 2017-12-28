var highlightindex = -1; //定义高亮显示索引,-1代表不高亮任何行 
var timeOutId = null; //定义延迟时间Id
var delayTime = 500; //默认延迟0.5秒
var minPrefix = 0; //定义最小几个字符开始搜索
var mouseOverCss = { background: "#cef", cursor: " pointer" }; //mouseover时样式
var mouseOutCss = { background: "white" }; //mouseout时样式

//var mouseOutCss = { "background-color": "white" };
var grayCss = { background: "#cef", cursor: " pointer" };
var upDownGrayCss = { background: "#cef" };
var upDownWhiteCss = { background: "white" };

var ajaxProcessUrl = "ashx/AutoCompleteHandler.ashx"; //发送ajax请求调用处理url

$(document).ready(function () {

    var wordInput = $("#txtQueryWord");
    var wordInputOffset = wordInput.offset();

    //隐藏自动补全框,并定义css属性
    $("#divAutoList").hide()
              .css("position", "absolute")
              .css("border", "1px black solid") //边框 黑色
              .css("top", wordInputOffset.top + wordInput.height() + 5 + "px")
              .css("left", wordInputOffset.left + "px")
              .css("padding", "3px")
              .css("background", "white")
              .width(wordInput.width() + 35);


    //给文本框添加键盘按下并弹起的事件
    wordInput.keyup(function(event) {
        var myEvent = event || window.event;
        var keyCode = myEvent.keyCode;
        var autoNode = $("#divAutoList"); //可供选择的项

        //        if (keyCode >= 65 && keyCode <= 90 || keyCode == 8 || keyCode == 46) { //输入字母,退格或删除,显示最新的内容
        if (keyCode != 13 && keyCode != 38 && keyCode != 40) { //不是三个特殊键，可以搜索
            var wordText = $("#txtQueryWord").val();
            if (wordText.length < minPrefix) return false;
            //取消上次提交
            //window.clearTimeout(timeOutId);
            timeOutId = setTimeout(function() {
                //ajax请求
                if (wordText != '') {
                    $.post(ajaxProcessUrl, { KeyWord: wordText }, function(data) {
                        var jqueryObj = $(data);
                        var wordNodes = jqueryObj.find("KeyWord"); //xml节点名
                        autoNode.html("");
                        wordNodes.each(function(i) {
                            var wrodNode = $(this);
                            var newDivNode = $("<div style='margin:0px'>").attr("id", i);
                            //newDivNode.html(wrodNode.text()).appendTo(autoNode); //xml文本内容( wrodNode.text() )
                            var txt = wrodNode.text().split(',');
                            newDivNode.html('<span style="float:left;width:70%;margin-left: 0px">' + txt[0] + '</span><span style="float:right;margin-right: 0px;text-align: right;width:30%">' + txt[1] + '篇 </span>').appendTo(autoNode);
                            //添加光标进入事件, 高亮节点
                            newDivNode.mouseover(function() {
                                //if (highlightindex != -1) {
                                //    $("#divAutoList").children("div")
                                //        .eq(highlightindex)
                                //        .css(mouseOverCss);
                                //}
                                highlightindex = $(this).attr("id");
                                $(this).children("span").css(grayCss);

                            });

                            //添加光标移出事件,取消高亮
                            newDivNode.mouseout(function() {
                                $(this).children("span").css(mouseOutCss);
                            });

                            //添加光标mousedown事件  点击事件newDivNode.click可能不起作用?
                            newDivNode.mousedown(function() {
                                //var comText = $(this).text();
                                var comText = $(this).find("span").eq(0).text();
                                $("#divAutoList").hide();
                                highlightindex = -1;
                                $("#txtQueryWord").val(comText);
                            });
                        });
                        if (wordNodes.length > 0) {
                            autoNode.show();
                        } else {
                            autoNode.hide();
                            highlightindex = -1;
                        }

                    }, "xml");
                } //xml结果集
            }, delayTime);
        }
        else if (keyCode == 38) {//输入向上,选中文字高亮
            var autoNodes = $("#divAutoList").children("div");
            if (highlightindex != -1) {
                autoNodes.eq(highlightindex).children("span").css(upDownWhiteCss);
                highlightindex--;
            }
            else {
                highlightindex = autoNodes.length - 1;
            }

            if (highlightindex == -1) {
                highlightindex = autoNodes.length - 1;
            }
            autoNodes.eq(highlightindex).children("span").css(upDownGrayCss);
        }
        else if (keyCode == 40) {//输入向下,选中文字高亮
            var autoNodes = $("#divAutoList").children("div");
            if (highlightindex != -1) {
                autoNodes.eq(highlightindex).children("span").css(upDownWhiteCss);
            }
            highlightindex++;
            if (highlightindex == autoNodes.length) {
                highlightindex = 0;
            }
            autoNodes.eq(highlightindex).children("span").css(upDownGrayCss);

        }
        else if (keyCode == 13) {//输入回车
            if (highlightindex != -1) {
                var comText = $("#divAutoList").hide().children("div").eq(highlightindex).children("span").eq(0).text();
                highlightindex = -1;
                $("#txtQueryWord").val(comText);
                return false;
            }
            else {
                //alert("文本框中的[" + $("#txtQueryWord").val() + "]被提交了！");
                $("#divAutoList").hide();
                $("#txtQueryWord").get(0).blur();
                return true;
            }
        }
    });

    //给查询框添加blur事件，隐藏提示层
    $("#txtQueryWord").blur(function() {
        $("#divAutoList").hide();
    });

});
