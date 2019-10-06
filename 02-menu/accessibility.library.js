'use strict'
let proxyArea = null
let menuUnderConstruction = null

mergeInto(LibraryManager.library, {  // eslint-disable-line
	accessibility_setup: function() {
		document.body.setAttribute('role', 'application')
		proxyArea = document.createElement('DIV')
		proxyArea.style.margin = '0.5rem'
		proxyArea.style.padding = '0.5rem'
		proxyArea.style.border = '0.1rem solid black'
		document.body.appendChild(proxyArea)
		proxyArea.focus()
	},

	accessibility_render_menu_start: function(ptrMenu) {
		const menuId = String(ptrMenu)
		let found = null

		for (const child of proxyArea.children) {
			if (child.id === menuId) {
				found = child
			}
			child.hidden = child.id !== menuId
		}

		if (!found) {
			const list = document.createElement('UL')
			list.id = menuId
			proxyArea.appendChild(list)
			menuUnderConstruction = list
		}
	},

	accessibility_render_menu_item: function(name, hasSubMenu) {
		if (menuUnderConstruction) {
			const listItem = document.createElement('LI')
			const menuButton = document.createElement('BUTTON')
			menuButton.innerText = UTF8ToString(name, 128)  // eslint-disable-line
			if (hasSubMenu) menuButton.setAttribute('aria-haspopup', 'true')
			menuButton.setAttribute('tabindex', '-1')
			listItem.appendChild(menuButton)
			menuUnderConstruction.appendChild(listItem)
		}
	},

	accessibility_render_menu_done: function() {
		menuUnderConstruction = null
	},

	accessibility_render_current_item: function(ptrMenu, itemNumber) {
		document.getElementById(String(ptrMenu))
			.children[itemNumber].firstChild.focus()
	}
})
