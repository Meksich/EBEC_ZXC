/* HtmlContent.h - HTML pages for WifiCtl
 * Created by BogdanDidukh2003 and maxrt, 10/04/2021
 */

#ifndef HTML_CONTENT_H_
#define HTML_CONTENT_H_

#define HTML_INDEX \
    "<!DOCTYPE html>\n" \
    "<html>\n" \
    "<head>\n" \
    " <title>Rover Control</title>\n" \
    "  <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js\"></script>\n" \
    "  <style>\n" \
    "    .filler {\n" \
    "       display: inline-block;\n" \
    "       width:100px;\n" \
    "       height:100px;\n" \
    "    }\n" \
    "   .filler_side {\n" \
    "       display: inline-block;\n" \
    "       width:35px;\n" \
    "       height:100px;\n" \
    "    }\n" \
    "    .btn {\n" \
    "       display: inline-block;\n" \
    "       width:100px;\n" \
    "       height:100px;\n" \
    "       background-color: red\n" \
    "    }\n" \
    "    .btn:active, .btn.active {\n" \
    "       background-color: green;\n" \
    "    }\n" \
    "  </style>\n" \
    "</head>\n" \
    "<body>\n" \
    " <div>\n" \
    "   <input type=\"checkbox\" id=\"delay\" name=\"delay\" checked>\n" \
    "   <label for=\"delay\">Delay 10s</label>\n" \
    "  </div>\n" \
    "  <div>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <div class=\"filler\"></div>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <button class=\"btn\" id=\"btn-w\">W</button>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <div class=\"filler\"></div>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <div class=\"filler\"></div>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <div class=\"filler\"></div>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <button class=\"btn\" id=\"btn-fwd\">Forward</button>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <div class=\"filler\"></div>\n" \
    "  </div>\n" \
    "  <div>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <button class=\"btn\" id=\"btn-a\">A</button>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <button class=\"btn\" id=\"btn-space\">Space</button>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <button class=\"btn\" id=\"btn-d\">D</button>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <div class=\"filler\"></div>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <button class=\"btn\" id=\"btn-left\">Left</button>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <button class=\"btn\" id=\"btn-mission\">Do Mision</button>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <button class=\"btn\" id=\"btn-right\">Right</button>\n" \
    "  </div>\n" \
    "  <div>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <div class=\"filler\"></div>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <button class=\"btn\" id=\"btn-s\">S</button>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <div class=\"filler\"></div>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <div class=\"filler\"></div>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <div class=\"filler\"></div>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <button class=\"btn\" id=\"btn-back\">Back</button>\n" \
    "    <div class=\"filler_side\"></div>\n" \
    "    <div class=\"filler\"></div>\n" \
    "  </div>\n" \
    "  <script>\n" \
    "     function sleep(ms) {\n" \
    "       return new Promise(resolve => setTimeout(resolve, ms));\n" \
    "     }\n" \
    "     async function sendRequest(uri) {\n" \
    "       if (document.getElementById('delay').checked) {\n" \
    "         await sleep(10000);\n" \
    "       }\n" \
    "       var xmlHttp = new XMLHttpRequest();\n" \
    "       xmlHttp.open('GET', uri, true);\n" \
    "       xmlHttp.send(null);\n" \
    "     }\n" \
    "     function buttonOn(buttonId) {\n" \
    "       $('#' + buttonId).addClass('active');\n" \
    "       $('#' + buttonId).click();\n" \
    "     }\n" \
    "     function buttonOff(buttonId) {\n" \
    "       $('#' + buttonId).removeClass('active');\n" \
    "     }\n" \
    "   </script>\n" \
    "   <script>\n" \
    "     $('#btn-fwd').on('click', () => { sendRequest('/move/fwd'); });\n" \
    "     $('#btn-back').on('click', () => { sendRequest('/move/back'); });\n" \
    "     $('#btn-left').on('click', () => { sendRequest('/move/left'); });\n" \
    "     $('#btn-right').on('click', () => { sendRequest('/move/right'); });\n" \
    "     $('#btn-w').on('click', () => { sendRequest('/crane/w'); });\n" \
    "     $('#btn-s').on('click', () => { sendRequest('/crane/s'); });\n" \
    "     $('#btn-a').on('click', () => { sendRequest('/crane/a'); });\n" \
    "     $('#btn-d').on('click', () => { sendRequest('/crane/d'); });\n" \
    "     $('#btn-space').on('click', () => { sendRequest('/crane/space'); });\n" \
    "     $('#btn-mission').on('click', () => { sendRequest('/mission'); });\n" \
    "     document.addEventListener('keydown', (e) => {\n" \
    "       if (e.code == 'ArrowUp') {\n" \
    "         buttonOn('btn-fwd');\n" \
    "       } else if (e.code == 'ArrowLeft') {\n" \
    "         buttonOn('btn-left');\n" \
    "       } else if (e.code == 'ArrowRight') {\n" \
    "         buttonOn('btn-right');\n" \
    "       } else if (e.code == 'ArrowDown') {\n" \
    "         buttonOn('btn-back');\n" \
    "       } else if (e.code == 'KeyW') {\n" \
    "          buttonOn('btn-w');\n" \
    "       } else if (e.code == 'KeyS') {\n" \
    "          buttonOn('btn-s');\n" \
    "       } else if (e.code == 'KeyA') {\n" \
    "          buttonOn('btn-a');\n" \
    "       } else if (e.code == 'KeyD') {\n" \
    "          buttonOn('btn-d');\n" \
    "       } else if (e.code == 'Space') {\n" \
    "          buttonOn('btn-space');\n" \
    "       } else if (e.code == 'KeyM') {\n" \
    "          buttonOn('btn-mission');\n" \
    "       }\n" \
    "     });\n" \
    "     document.addEventListener('keyup', (e) => {\n" \
    "       if (e.code == 'ArrowUp') {\n" \
    "         buttonOff('btn-fwd');\n" \
    "       } else if (e.code == 'ArrowLeft') {\n" \
    "         buttonOff('btn-left');\n" \
    "       } else if (e.code == 'ArrowRight') {\n" \
    "         buttonOff('btn-right');\n" \
    "       } else if (e.code == 'ArrowDown') {\n" \
    "         buttonOff('btn-back');\n" \
    "       } else if (e.code == 'KeyW') {\n" \
    "         buttonOff('btn-w');\n" \
    "       } else if (e.code == 'KeyS') {\n" \
    "         buttonOff('btn-s');\n" \
    "       } else if (e.code == 'KeyA') {\n" \
    "         buttonOff('btn-a');\n" \
    "       } else if (e.code == 'KeyD') {\n" \
    "         buttonOff('btn-d');\n" \
    "       } else if (e.code == 'Space') {\n" \
    "         buttonOff('btn-space');\n" \
    "       } else if (e.code == 'KeyM') {\n" \
    "         buttonOff('btn-mission');\n" \
    "       }\n" \
    "     });\n" \
    "   </script>\n" \
    "</body>\n" \
    "</html>"

#define HTML_404 \
    "<!DOCTYPE html><html>" \
    "<head>" \
    "<title>404 - Rover Control</title>" \
    "</head>" \
    "<body>" \
    "<h1>404 Not Found</h1>" \
    "<p>Requested resource does not exist.</p>" \
    "</body>" \
    "</html>"

#endif
