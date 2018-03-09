var highlightindex = -1; //���������ʾ����,-1���������κ��� 
var timeOutId = null; //�����ӳ�ʱ��Id
var delayTime = 500; //Ĭ���ӳ�0.5��
var minPrefix = 0; //������С�����ַ���ʼ����
var mouseOverCss = { background: "#cef", cursor: " pointer" }; //mouseoverʱ��ʽ
var mouseOutCss = { background: "white" }; //mouseoutʱ��ʽ

//var mouseOutCss = { "background-color": "white" };
var grayCss = { background: "#cef", cursor: " pointer" };
var upDownGrayCss = { background: "#cef" };
var upDownWhiteCss = { background: "white" };

var ajaxProcessUrl = "ashx/AutoCompleteHandler.ashx"; //����ajax������ô���url

$(document).ready(function () {

    var wordInput = $("#txtQueryWord");
    var wordInputOffset = wordInput.offset();

    //�����Զ���ȫ��,������css����
    $("#divAutoList").hide()
              .css("position", "absolute")
              .css("border", "1px black solid") //�߿� ��ɫ
              .css("top", wordInputOffset.top + wordInput.height() + 5 + "px")
              .css("left", wordInputOffset.left + "px")
              .css("padding", "3px")
              .css("background", "white")
              .width(wordInput.width() + 35);


    //���ı�����Ӽ��̰��²�������¼�
    wordInput.keyup(function(event) {
        var myEvent = event || window.event;
        var keyCode = myEvent.keyCode;
        var autoNode = $("#divAutoList"); //�ɹ�ѡ�����

        //        if (keyCode >= 65 && keyCode <= 90 || keyCode == 8 || keyCode == 46) { //������ĸ,�˸��ɾ��,��ʾ���µ�����
        if (keyCode != 13 && keyCode != 38 && keyCode != 40) { //�����������������������
            var wordText = $("#txtQueryWord").val();
            if (wordText.length < minPrefix) return false;
            //ȡ���ϴ��ύ
            //window.clearTimeout(timeOutId);
            timeOutId = setTimeout(function() {
                //ajax����
                if (wordText != '') {
                    $.post(ajaxProcessUrl, { KeyWord: wordText }, function(data) {
                        var jqueryObj = $(data);
                        var wordNodes = jqueryObj.find("KeyWord"); //xml�ڵ���
                        autoNode.html("");
                        wordNodes.each(function(i) {
                            var wrodNode = $(this);
                            var newDivNode = $("<div style='margin:0px'>").attr("id", i);
                            //newDivNode.html(wrodNode.text()).appendTo(autoNode); //xml�ı�����( wrodNode.text() )
                            var txt = wrodNode.text().split(',');
                            newDivNode.html('<span style="float:left;width:70%;margin-left: 0px">' + txt[0] + '</span><span style="float:right;margin-right: 0px;text-align: right;width:30%">' + txt[1] + 'ƪ </span>').appendTo(autoNode);
                            //��ӹ������¼�, �����ڵ�
                            newDivNode.mouseover(function() {
                                //if (highlightindex != -1) {
                                //    $("#divAutoList").children("div")
                                //        .eq(highlightindex)
                                //        .css(mouseOverCss);
                                //}
                                highlightindex = $(this).attr("id");
                                $(this).children("span").css(grayCss);

                            });

                            //��ӹ���Ƴ��¼�,ȡ������
                            newDivNode.mouseout(function() {
                                $(this).children("span").css(mouseOutCss);
                            });

                            //��ӹ��mousedown�¼�  ����¼�newDivNode.click���ܲ�������?
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
                } //xml�����
            }, delayTime);
        }
        else if (keyCode == 38) {//��������,ѡ�����ָ���
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
        else if (keyCode == 40) {//��������,ѡ�����ָ���
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
        else if (keyCode == 13) {//����س�
            if (highlightindex != -1) {
                var comText = $("#divAutoList").hide().children("div").eq(highlightindex).children("span").eq(0).text();
                highlightindex = -1;
                $("#txtQueryWord").val(comText);
                return false;
            }
            else {
                //alert("�ı����е�[" + $("#txtQueryWord").val() + "]���ύ�ˣ�");
                $("#divAutoList").hide();
                $("#txtQueryWord").get(0).blur();
                return true;
            }
        }
    });

    //����ѯ�����blur�¼���������ʾ��
    $("#txtQueryWord").blur(function() {
        $("#divAutoList").hide();
    });

});
