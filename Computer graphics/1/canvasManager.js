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
        this._offset = {x: 0, y: 0};
        this._scale = {x: 1, y: 1};
    }

    setOffset(x, y) {
        this._offset.x = x;
        this._offset.y = y;
    }

    setScale(x, y) {
        this._scale.x = x;
        this._scale.y = y;
    }

    getMousePosition(event) {
        if (event) {
            let rect = this._canvas.getBoundingClientRect();
            return this._toVirtualCoordinates({
                x: event.clientX - rect.left,
                y: event.clientY - rect.top
            });
        } else {
            return undefined;
        }
    }

    clear() {
        let context = this._canvas.getContext('2d');
        context.clearRect(0, 0, this._canvas.width, this._canvas.height);
    }

    drawLine(p1, p2, options) {
        if (!options) {
            options = {}
        }

        p1 = this._toScreenCoordinates(p1);
        p2 = this._toScreenCoordinates(p2);

        let context = this._canvas.getContext('2d');
        context.beginPath();

        context.lineWidth = options.lineWidth || 1;
        context.strokeOpacity = options.opacity || 1;
        context.strokeStyle = options.color || 'black';

        context.moveTo(p1.x, p1.y);
        context.lineTo(p2.x, p2.y);
        context.stroke();

        context.closePath();
    }

    drawPoint(options) {
        if (!options) return false;
        if (!options.point || !(isFinite(options.point.x) && isFinite(options.point.y))) return false;

        let point = options.point;
        if (!point) return false;
        let screenPoint = this._toScreenCoordinates(point);
        let x = screenPoint.x;
        let y = screenPoint.y;
        if (!(x && y)) return false;
        let color = options.color || 'black';
        let radius = options.radius || 4;

        let context = this._canvas.getContext("2d");

        context.beginPath();
        context.fillStyle = context.strokeStyle = color;
        context.arc(x, y, radius, 0, 2 * Math.PI);
        context.fill();
        context.closePath();

        return true;
    }

    drawPoints(options) {
        if (!options) return false;
        let points = options.points;
        if (!points) return false;

        return points.forEach(function (point) {
            options.point = point;
            return this.drawPoint(options);
        }.bind(this));
    }

    drawGrid(options) {
        if (!options) {
            options = {};
        }
        options.color = options.color || 'gray';
        options.lineWidth = options.lineWidth || 1;
        options.axisWidth = options.axisWidth || 3;
        options.axisColor = options.axisColor || 'pink';
        let step = options.step || 10;

        let top = this._toVirtualCoordinates({x: 0, y: 0});
        let bottom = this._toVirtualCoordinates({x: this._canvas.width, y: this._canvas.height});

        for (let x = Math.round(top.x / step) * step; x <= bottom.x; x += step) {
            this.drawLine(
                {x: x, y: top.y},
                {x: x, y: bottom.y},
                options
            );
        }

        for (let y = Math.round(top.y / step) * step; y <= bottom.y; y += step) {
            this.drawLine(
                {x: top.x, y: y},
                {x: bottom.x, y: y},
                options
            );
        }

        this.drawLine(
            top,
            {x: top.x, y: bottom.y},
            options
        );
        this.drawLine(
            top,
            {x: bottom.x, y: top.y},
            options
        );
        this.drawLine(
            {x: bottom.x, y: top.y},
            {x: bottom.x, y: bottom.y},
            options
        );
        this.drawLine(
            {x: top.x, y: bottom.y},
            {x: bottom.x, y: bottom.y},
            options
        );

        options.lineWidth = options.axisWidth;
        options.color = options.axisColor;
        this.drawLine(
            {x: top.x, y: 0},
            {x: bottom.x, y: 0},
            options
        );
        this.drawLine(
            {x: 0, y: top.y},
            {x: 0, y: bottom.y},
            options
        )
    }

    _toScreenCoordinates(point) {
        return {
            x: (this._offset.x + point.x) * this._scale.x,
            y: (this._offset.y + point.y) * this._scale.y,
        }
    }

    _toVirtualCoordinates(point) {
        return {
            x: point.x / this._scale.x - this._offset.x,
            y: point.y / this._scale.y - this._offset.y
        }
    }
}