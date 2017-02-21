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

        this._gridVisibility = options.gridVisibility || true;
        this._gridStep = options.gridStep || 10;
        this._gridColor = options.gridColor || 'gray';
        this._gridOpacity = options.gridOpacity || 1;

        this._drawGrid();
    }

    get gridVisibility() {
        return this._gridVisibility;
    }

    get gridStep() {
        return this._gridStep;
    }

    get gridColor() {
        return this._gridColor;
    }

    get gridOpacity() {
        return this._gridOpacity;
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

    _drawGrid() {
        if (!this._gridVisibility) {
            return;
        }

        let context = this._canvas.getContext("2d");
        context.beginPath();
        for (let x = 0.5; x <= this._canvas.width; x += this._gridStep) {
            context.moveTo(x, 0);
            context.lineTo(x, this._canvas.height);
        }

        for (let y = 0.5; y <= this._canvas.height; y += this._gridStep) {
            context.moveTo(0, y);
            context.lineTo(this._canvas.width, y);
        }

        context.moveTo(this._canvas.width - 0.5, 0.5);
        context.lineTo(this._canvas.width - 0.5, this._canvas.height - 0.5);
        context.moveTo(0.5, this._canvas.height - 0.5);
        context.lineTo(this._canvas.width - 0.5, this._canvas.height - 0.5);

        context.strokeStyle = this._gridColor;
        context.strokeOpacity = this._gridOpacity;
        context.stroke();

        context.closePath();
    }
}