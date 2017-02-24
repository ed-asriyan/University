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
        this._points = [];

        this._grid = options.grid ||
            {
                xStep: 10,
                yStep: 10,
                color: 'gray',
                border: true,
                visible: true,
            };

        this._drawGrid();
    }

    get points() {
        return this._points;
    }

    set points(value) {
        if (value) {
            this._points = value.slice();
        }
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
        context.strokeOpacity = options.opacity || 1;

        context.moveTo(x1, y1);
        context.lineTo(x2, y2);
        context.stroke();

        context.closePath();
    }

    addPoint(x, y, color) {
        this._points.push({
            x: x,
            y: y,
            color: color || 'black',
            radius: 2.5
        });
    }

    getImageData() {
        let ctx = this._canvas.getContext('2d');
        return ctx.getImageData(0, 0, this._canvas.width, this._canvas.height);
    }

    putImageData(src) {
        if (src) {
            let ctx = this._canvas.getContext('2d');
            ctx.putImageData(src, 0, 0);
        }
    }

    _drawGrid() {
        if (!this._grid.visible) return;

        let context = this._canvas.getContext("2d");
        context.beginPath();
        for (let x = 0.5; x <= this._canvas.width; x += this._grid.xStep) {
            context.moveTo(x, 0);
            context.lineTo(x, this._canvas.height);
        }

        for (let y = 0.5; y <= this._canvas.height; y += this._grid.yStep) {
            context.moveTo(0, y);
            context.lineTo(this._canvas.width, y);
        }

        if (this._grid.border) {
            context.moveTo(this._canvas.width - 0.5, 0.5);
            context.lineTo(this._canvas.width - 0.5, this._canvas.height - 0.5);
            context.moveTo(0.5, this._canvas.height - 0.5);
            context.lineTo(this._canvas.width - 0.5, this._canvas.height - 0.5);
        }

        context.strokeStyle = this._grid.color;
        context.stroke();

        context.closePath();
    }

    reDraw() {
        let context = this._canvas.getContext("2d");
        context.clearRect(0, 0, this._canvas.width, this._canvas.height);

        this._drawGrid();

        context = this._canvas.getContext("2d");
        this._points.forEach(function (point) {
            if (point.x && point.y) {
                context.beginPath();
                context.fillStyle = context.strokeStyle = point.color;
                context.arc(point.x, point.y, point.radius, 0, 2 * Math.PI);
                context.fill();
                context.closePath();
            }
        });
    }
}