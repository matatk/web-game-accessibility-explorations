'use strict'
let proxyArea = null
let pageUnderConstruction = null

mergeInto(LibraryManager.library, {  // eslint-disable-line
	accessibility_setup: function() {
		document.body.setAttribute('role', 'application')
		proxyArea = document.getElementById('proxy-ui')
		proxyArea.focus()
	},

	accessibility_render_page_start: function(ptrPage) {
		const pageId = String(ptrPage)
		proxyArea.innerHTML = ''
		const list = document.createElement('UL')
		list.id = pageId
		proxyArea.appendChild(list)
		pageUnderConstruction = list
	},

	accessibility_render_page_item: function(name, widgetType) {
		if (pageUnderConstruction) {
			const listItem = document.createElement('LI')
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
					element = document.createElement('button')
					element.setAttribute('aria-haspopup', 'true')
					element.innerText = string
					break
				case 3:  // CONTAINER
					element = document.createElement('button')
					element.innerText = string
					break
				case 4:  // LABEL
					element = document.createElement('label')
					element.innerText = string
					break
				case 5:  // TEXTBOX
					element = document.createElement('input')
					element.setAttribute('aria-label', string)
					break
				case 6:  // SLIDER
					element = document.createElement('input')
					element.type = 'range'
					element.innerText = string
					break
			}

			element.setAttribute('tabindex', '-1')
			listItem.appendChild(element)
			pageUnderConstruction.appendChild(listItem)
		}
	},

	accessibility_render_page_done: function() {
		pageUnderConstruction = null
	},

	accessibility_render_current_item: function(ptrPage, itemNumber) {
		document.getElementById(String(ptrPage))
			.children[itemNumber].firstChild.focus()
	}
})
