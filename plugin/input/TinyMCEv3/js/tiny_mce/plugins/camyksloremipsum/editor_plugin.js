(function() {
  // Load plugin specific language pack
  tinymce.PluginManager.requireLangPack('camyksloremipsum');
  
  tinymce.create('tinymce.plugins.CaMykSLoremIpsumPlugin', {
    init : function(ed, url) {
      /* register command */
      ed.addCommand('camyksLoremIpsum', function() {
        ed.windowManager.confirm('camyksloremipsum.warning', function(s) {
	  if (s)
	    ed.execCommand('mceSetContent', false, 
			   '<h1 class="eTitle1">Lorem ipsum dolor sit amet.</h1>'+
			   '<h2 class="eTitle2">Consectetuer adipiscing elit.</h2>'+
			   '<h3 class="eTitle3">In quis nisl ut erat rutrum porta.</h3>'+
			   '<h4 class="eTitle4">Donec risus libero, dictum quis, aliquam sit amet, rutrum id, orci.</h4>'+
			   '<p class="eContent1">Lorem ipsum dolor sit amet, consectetuer adipiscing elit.'+
			   ' In quis nisl ut erat rutrum porta. Donec risus libero, dictum quis, aliquam sit amet, rutrum id, orci.'+
			   ' Maecenas pellentesque commodo turpis. Aliquam suscipit sem eget sem. Integer elementum turpis ut ipsum.'+
			   ' Maecenas in justo. Donec aliquet ornare tellus. Suspendisse potenti. Nunc ante.'+
			   ' Mauris eros ligula, pharetra sed, mattis vitae, molestie eu, diam. Nullam sollicitudin imperdiet nisi.</p>'+
			   '<ul><li class="eContent1">Lorem ipsum dolor <a href="http://www.camyks.net" class="eLink1">sit amet</a>,</li>'+
			   '<li class="eContent1">Consectetuer <a href="http://www.camyks.net" class="eLink2">adipiscing elit</a>.</li></ul>'+
			   '<p class="eContent2">Etiam eros erat, pretium aliquet, blandit ut, elementum fermentum, sapien. Sed erat arcu,'+
			   ' consequat a, consequat vel, suscipit id, turpis. Morbi et nisl. Nam mauris pede, porttitor quis,'+
			   ' consequat sit amet, tempus et, elit. Vivamus faucibus. Morbi diam. Maecenas dapibus nulla in sapien.'+
			   ' Aliquam bibendum mollis mauris. Fusce tortor lorem, mollis sed, accumsan ac, condimentum a, massa.'+
			   ' Ut dapibus porttitor pede. Praesent vel arcu id sem venenatis volutpat.'+
			   ' Aenean vulputate nisl ut nisi ornare consectetuer.</p>'+
			   '<table border="0" width="80%" align="center" class="eTable"><tbody>'+
			   '<tr><td class="eTableHeader">&nbsp;Lorem ipsum dolor sit amet.<br /></td><td class="eTableHeader">&nbsp;Consectetuer adipiscing elit.</td></tr>'+
			   '<tr><td class="eTableLine0">In quis nisl ut erat rutrum porta.</td><td class="eTableLine0">Donec risus libero, dictum quis,</td></tr>'+
			   '<tr><td class="eTableLine1">Donec risus libero, dictum quis,</td><td class="eTableLine1">In quis nisl ut erat rutrum porta.</td></tr>'+
			   '<tr><td class="eTableLine0">In quis nisl ut erat rutrum porta.</td><td class="eTableLine0">Donec risus libero, dictum quis,</td></tr>'+
			   '<tr><td class="eTableLine1">Donec risus libero, dictum quis,</td><td class="eTableLine1">In quis nisl ut erat rutrum porta.</td></tr></tbody></table>'+
			   '<p class="eContent3">Phasellus porta, erat in mollis facilisis, odio augue vulputate odio,'+
			   ' ornare rhoncus dui erat quis est. Nam ut lectus. Duis laoreet quam vel nunc. Ut est nulla,'+
			   ' tincidunt vitae, pharetra in, tempor ac, augue. Nunc sem sapien, feugiat et, luctus sit amet,'+
			   ' sodales at, nisl. Suspendisse mollis laoreet orci. Nunc in tortor. Pellentesque habitant morbi'+
			   ' tristique senectus et netus et malesuada fames ac turpis egestas. Aliquam dui augue, fermentum sed,'+
			   ' congue et, adipiscing ut, augue. Phasellus odio. Fusce interdum, nulla ut consectetuer euismod,'+
			   ' odio nibh luctus mauris, nec vulputate lacus libero eu ligula. Aliquam erat volutpat. Morbi sagittis'+
			   ' ligula fringilla mi. Integer pretium, mauris at condimentum congue, lorem purus varius velit,'+
			   ' vel aliquam elit nulla tempor lectus. Sed rhoncus. Curabitur facilisis semper lorem. Proin porttitor leo sed neque.</p>'+
			   '<p class="eContent4">Maecenas at pede sit amet nisl posuere rutrum. Etiam elit. Proin consequat felis a magna.'+
			   ' Etiam faucibus sollicitudin purus. Nunc purus neque, suscipit in, dignissim a, blandit lacinia, lectus.'+
			   ' Sed gravida. Cras at odio sit amet dui mollis viverra. Etiam ultrices tellus nec magna. Ut tempor.'+
			   ' Vestibulum semper lorem et mi. Nunc euismod dapibus nisi. Nullam molestie iaculis urna. Donec at ligula.'+
			   ' Nullam facilisis augue mattis magna. Nunc imperdiet. Class aptent taciti sociosqu ad litora torquent'+
			   ' per conubia nostra, per inceptos himenaeos. Nam semper orci. Curabitur volutpat, felis eget mattis pulvinar,'+
			   ' magna quam varius diam, in suscipit justo augue in justo. Sed eu elit.</p>'
			   
			   );
	});
      });
      
      /* register command button */
      ed.addButton('camyksloremipsum', {
	title : 'camyksloremipsum.desc',
	  cmd : 'camyksLoremIpsum',
	  image : url + '/img/icon.gif'
	  });
    },
      
      /* no control */
      createControl : function(n, cm) {
	return null;
      },
      
      /* set plugin infos */
      getInfo : function() {
	return {
	  longname : 'CaMykS Lorem Ipsum',
	    author : 'CaMykS Team',
	    authorurl : 'http://www.camyks.net',
	    infourl : '',
	    version : "1.0"
			};
      }
      });
  
  /* register plugin */
  tinymce.PluginManager.add('camyksloremipsum', tinymce.plugins.CaMykSLoremIpsumPlugin);
})();
