$(function() {

  var createAccordion = function(accordionElem) {
    var accrdToggle = function(e) {
      e.preventDefault();
      $(this).next().slideToggle();
    };
    $(accordionElem).click(accrdToggle).next().hide();
  };


  function Grid(canvasDiv, dimensions, dim, fgColor,
    bgColor, gColor, nlColor, shColor) {
    var self = this;

    this.canvasDiv = canvasDiv;
    this.dimensions = dimensions;
    this.fgColor = fgColor;
    this.bgColor = bgColor;
    this.gColor = gColor;
    this.nlColor = nlColor;
    this.shColor = shColor;

    this.click = 0;

    var $inError = [];
    var $mathMsg = [];

    var sizePx = dim * dimensions;

    var $bgCanvas = $('<canvas/>', {
      'class': 'bgCanvas',
      Width: sizePx,
      Height: sizePx,
    });
    var $fgCanvas = $('<canvas/>', {
      'class': 'fgCanvas',
      Width: sizePx,
      Height: sizePx
    });
    $(canvasDiv).append($bgCanvas).append($fgCanvas).height(sizePx).width(
      sizePx);
    var valArray = [];

    // $.getScript('parser.js');


    this.drawBg = function() {
      //fill background
      var ctx = $bgCanvas[0].getContext('2d');
      ctx.fillStyle = bgColor;
      ctx.fillRect(0, 0, sizePx, sizePx);
      //draw grid
      ctx.fillStyle = gColor;

      for (i = 0; i <= dimensions; i++) {
        for (j = i % 2; j <= dimensions; j += 2) {
          ctx.fillRect(i * dim, j * dim, dim, dim);
        }
      }
      //stroke the middle
      ctx.beginPath();
      ctx.strokeStyle = nlColor;
      ctx.lineWidth = dim;
      var middleY = dimensions - Math.floor(dimensions / 2.0) - 1;
      var middleX = Math.floor(dimensions / 2.0);
      //horizontal
      ctx.moveTo(0, middleY * dim + dim / 2);
      ctx.lineTo(sizePx, middleY * dim + dim / 2);
      //vertical
      ctx.moveTo(middleX * dim + dim / 2, 0);
      ctx.lineTo(middleX * dim + dim / 2, sizePx);
      ctx.stroke();
    };
    this.resetArray = function() {
      if (valArray.length < 256) {
        valArray = [];
        for (var i = 0; i < dimensions; i++) {
          valArray[valArray.length] = i - dimensions / 2;
        }
      } else {
        for (var j = 0; j < valArray.length; j++) {
          valArray[j] = j - dimensions / 2;
        }
      }
    };
    this.drawMember = function(index) {
      var ctx = $fgCanvas[0].getContext('2d');
      var minus = dimensions / 2 + 1;
      var x = index * dim;
      var y = (dimensions - (valArray[index] + minus));
      //clear column
      ctx.clearRect(x, 0, dim, sizePx);
      //draw pixel
      ctx.fillStyle = fgColor;
      y *= dim;
      ctx.fillRect(x, y, dim, dim);
      ctx.beginPath();
      ctx.strokeStyle = shColor;
      ctx.lineWidth = dim;
      ctx.moveTo(x + (dim / 2), y + dim);
      ctx.lineTo(x + (dim / 2), sizePx);
      ctx.stroke();
    };

    this.redrawArray = function() {
      for (var i = dimensions - 1; i >= 0; i--) {
        self.drawMember(i);
      }
    };
    this.clickHandler = function(x, y) {
      cx = Math.trunc(Math.floor(x) / 3);
      cy = self.dimensions - Math.trunc(Math.floor(y) / 3) - 1;
      valArray[cx] = cy - dimensions / 2;
      self.drawMember(cx);
    };
    this.outputArray = function() {
      var outString = '';
      for (var i = 0; i < valArray.length - 1; i++) {
        outString += '' + (valArray[i] + 128) + ', ';
      }
      outString += (valArray[valArray.length - 1] + 128);
      $('#outBox').val(outString);
    };
    this.clearInput = function() {
      $('#inBox').val('');
    };
    this.parseInput = function() {
      var strToParse = $('#inBox').val();
      if (strToParse.length === 0) {
        $inError.text('Input cannot be empty!').fadeIn();
        return;
      }
      var tokenizedString = strToParse.split(', ');
      var sanitizedString = [];

      for (var i = 0; i < tokenizedString.length; i++) {
        var currNum = parseInt(tokenizedString[i]);
        if (currNum < 0 || currNum > 255) {
          $inError.text(
            'Only unsigned byte values allowed (-128 - 127)!');
          return;
        }
        sanitizedString[sanitizedString.length] = currNum - 128;
      }

      if (sanitizedString.length != 256) {
        $inError.text(
          'Your input must contain exactly 256 numbers! Currently, it contains ' +
          sanitizedString.length + '. ').fadeIn();
        return;
      }
      $inError.text('').hide();
      valArray = sanitizedString.slice();
      self.redrawArray();
    };

    this.parseMath = function() {

      var variables = {
        x: 0,
        xs: 0,
        s: 1 / 256,
        e: 2.7182818284,
        pi: 3.141592653589793,
        phi: 1.6180339887498,
        'u(x)': x*4
      };

      var mathString = $('#mathInp').val();
      if (mathString.length === 0) $mathMsg.text(
        "Empty expression!").removeClass().addClass('error').fadeIn();

      var x = -1;
      var inc = 1 / 128;

      var expr2 = Parser.parse(mathString);
      for (var i = 0; i < valArray.length; i++) {
        try {
          variables.x = x;
          variables.xs = x * variables.pi;
          var result = expr2.evaluate(variables);
          result *= 128;
          result = Math.round(result);
          if (result < -128) result = -128;
          if (result > 127) result = 127;
          valArray[i] = result;
          x += inc;
        } catch (err) {
          $mathMsg.text(err).removeClass().addClass('error').fadeIn();
          return;
        }
      }

      self.redrawArray();
      $mathMsg.text('Parsed successfully!').removeClass().addClass(
        'positive').fadeIn();

    };
    this.init = function() {
      this.drawBg();
      this.resetArray();
      this.redrawArray();

      // click detection - draw only on clicks
      var clicked = false;
      $("body").mousedown(function() {
        clicked = true;
      });
      $("body").mouseup(function() {
        clicked = false;
      });

      // drawing position handler when over canvas
      var posHandler = function(e) {
        var offset = $fgCanvas.offset();
        var x = e.pageX - offset.left;
        var y = e.pageY - offset.top;
        self.clickHandler(x, y);
      };

      //set that handler on events
      $fgCanvas.mouseover(function(e) {
        if (clicked) posHandler(e);
      });
      $fgCanvas.mousemove(function(e) {
        if (clicked) posHandler(e);
      });
      $fgCanvas.click(function(e) {
        posHandler(e);
      });

      //button handlers
      $('#export').click(self.outputArray);
      $('#reset').click(function() {
        self.resetArray();
        self.redrawArray();
      });
      $('#parse').click(self.parseInput);
      $('#inBox').bind("enterKey", self.parseInput);
      $('#inBox').keydown(function(event) {
        if (event.keyCode == 13) {
          self.parseInput();
          event.preventDefault();
        }
      });
      $('#clear').click(self.clearInput);
      $('#mathParse').click(self.parseMath);
      $('#mathInp').bind("enterKey", self.parseMath);
      $('#mathInp').keydown(function(event) {
        if (event.keyCode == 13) {
          self.parseMath();
        }
      });

      //sizes
      $('#outBox').prop('readonly', true).width(sizePx);
      $(
        '#inBox').width(sizePx);
      $('#mathInp').width(sizePx - 20);

      //create error message for input
      $inError = $('<p class="error"></p>').hide();
      $mathMsg = $('<p></p>').hide();
      $('#inBox').after($inError);
      $('#mathInp').after($mathMsg);
    };

    this.init();
  }

  var waveGrid = new Grid('.waveform', 256, 3, 'rgb(233,233,228)',
    'rgb(39,30,34)', 'rgb(62,61,50)', 'rgb(239,38,114)',
    'rgba(233,233,228, 0.1)');

  createAccordion("a.accordion");
});
