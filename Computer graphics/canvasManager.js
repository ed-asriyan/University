'use strict';

/**
 * Created by ed on 18.02.17.
 */
class CanvasManager {
    constructor(canvas, options) {
        if (!options) {
            options = {}
        }

        this._canvas = canvas;
    }

    getMousePosition(event) {
        if (event) {
            let rect = this._canvas.getBoundingClientRect();
            return {
                x: event.clientX - rect.left,
                y: event.clientY - rect.top
            };
        } else {
            return undefined;
        }
    }

    drawLine(x1, y1, x2, y2, options) {
        if (!options) {
            options = {}
        }

        let context = this._canvas.getContext('2d');
        context.beginPath();

        context.lineWidth = options.lineWidth || 1;
        context.strokeStyle = options.color || 'black';
        context.strokeOpacity = options.opacity || 1;

        context.moveTo(x1, y1);
        context.lineTo(x2, y2);
        context.stroke();

        context.closePath();
    }

    drawPoint(x, y, options) {
        if (!options) {
            options = {}
        }

        let context = this._canvas.getContext('2d');
        context.beginPath();

        context.fillStyle = context.strokeStyle = options.color || 'black';

        context.arc(x, y, options.width / 2 || 1, 0, 2 * Math.PI, false);

        context.fill();
        context.closePath();
    }

    getImageData() {
        let ctx = this._canvas.getContext('2d');
        return ctx.getImageData(0, 0, this._canvas.width, this._canvas.height);
    }

    putImageData(src) {
        if (src) {
            let ctx = this._canvas.getContext('2d');
            // let data = JSON.parse(src);
            ctx.putImageData(src, 0, 0);
        }
    }

    drawGrid(options) {
        if (!options) {
            options = {};
        }

        let gridXStep = options.gridXStep || options.gridYStep || options.gridStep || 10;
        let gridYStep = options.gridYStep || options.gridXStep || options.gridStep || 10;
        let gridColor = options.gridColor || 'gray';
        let gridOpacity = options.gridOpacity || 1;
        let gridBorder = options.gridBorder || (options.gridBorder == undefined);

        let context = this._canvas.getContext("2d");
        context.beginPath();
        for (let x = 0.5; x <= this._canvas.width; x += gridXStep) {
            context.moveTo(x, 0);
            context.lineTo(x, this._canvas.height);
        }

        for (let y = 0.5; y <= this._canvas.height; y += gridYStep) {
            context.moveTo(0, y);
            context.lineTo(this._canvas.width, y);
        }

        if (gridBorder) {
            context.moveTo(this._canvas.width - 0.5, 0.5);
            context.lineTo(this._canvas.width - 0.5, this._canvas.height - 0.5);
            context.moveTo(0.5, this._canvas.height - 0.5);
            context.lineTo(this._canvas.width - 0.5, this._canvas.height - 0.5);
        }

        context.strokeStyle = gridColor;
        context.strokeOpacity = gridOpacity;
        context.stroke();

        context.closePath();
    }
}