'use strict'
let proxyArea
let currentLabel

mergeInto(LibraryManager.library, {  // eslint-disable-line
	accessibility_setup: function() {
		document.body.setAttribute('role', 'application')
		proxyArea = document.getElementById('proxy-ui')
		proxyArea.focus()
		currentLabel = null
	},

	accessibility_render_page_start: function() {
		proxyArea.innerHTML = ''
	},

	accessibility_render_item: function(name, widgetType, widgetPtr, parentPtr) {
		const string = UTF8ToString(name, 128)  // eslint-disable-line
		let element = null

		switch (widgetType) {
			case 0:  // WIDGET
				element = document.createElement('span')
				element.innerText = string
				break
			case 1:  // BUTTON
				element = document.createElement('button')
				element.innerText = string
				break
			case 2:  // SUBPAGE
				element = document.createElement('a')
				element.href = '#'
				element.innerText = string
				break
			case 3:  // CONTAINER
				if (document.querySelector('fieldset')) {
					element = document.createElement('div')
				} else {
					element = document.createElement('fieldset')
					element.appendChild(document.createElement('legend'))
					element.firstChild.innerText = string
				}
				break
			case 4:  // LABEL
				element = document.createElement('label')
				element.innerText = string
				currentLabel = element
				break
			case 5:  // TEXTBOX
				element = document.createElement('input')
				break
			case 6:  // SLIDER
				element = document.createElement('input')
				element.type = 'range'
				break
		}

		element.id = widgetPtr
		element.setAttribute('tabindex', '-1')

		if (currentLabel === null || currentLabel === element) {
			const widgetWrapper = document.createElement('div')
			widgetWrapper.appendChild(element)

			if (parentPtr !== 0) {
				const parentElement = document.getElementById(parentPtr)
				parentElement.appendChild(widgetWrapper)
			} else {
				proxyArea.appendChild(widgetWrapper)
			}
		} else {
			currentLabel.appendChild(element)
			currentLabel = null
		}
	},

	accessibility_render_page_done: function() {
		// noop
	},

	accessibility_set_focus: function(widgetPtr) {
		document.getElementById(String(widgetPtr)).focus()
	}
})
