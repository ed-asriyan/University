'use strict';

/**
 * Created by ed on 18.02.17.
 */
class CanvasManager {
    constructor(canvas) {
        this._canvas = canvas;

        this._mousePositionLabal = document.createElement('label');
        this._showMousePositionLabel = true;
        this._mousePositionLabal.style.position = 'fixed';
        this._canvas.addEventListener('mouseleave', this._onMouseLeave.bind(this));
        this._canvas.addEventListener('mousemove', this._onMouseMove.bind(this));
        this._canvas.parentNode.appendChild(this._mousePositionLabal);
    }

    get showMousePositionLabel() {
        return this._showMousePositionLabel;
    }

    set showMousePositionLabel(value) {
        this._showMousePositionLabel = value.valueOf();
    }

    /**
     * Returns mouse position.
     * @param event Event
     * @returns {*}
     */
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

    _updateMousePositionLabel(event) {
        if (!this._showMousePositionLabel) {
            return;
        }

        if (!event) {
            this._mousePositionLabal.style.display = 'none';
        } else {
            let mousePos = this.getMousePosition(event);
            if (mousePos === null) {
                this._mousePositionLabal.style.display = 'none';
            } else {
                let xPos = mousePos.x + 20;
                let yPos = mousePos.y + 25;

                this._mousePositionLabal.style.left = xPos + 'px';
                this._mousePositionLabal.style.top = yPos + 'px';

                this._mousePositionLabal.innerHTML = mousePos.x + ", " + mousePos.y;
                this._mousePositionLabal.style.display = 'inline';
            }
        }
    }

    _onMouseMove(e) {
        this._updateMousePositionLabel(e);
    }

    _onMouseLeave(e) {
        this._updateMousePositionLabel(undefined);
    }
}