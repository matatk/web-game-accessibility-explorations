'use strict'
let ui

mergeInto(LibraryManager.library, {
	accessibility_setup: function() {
		ui = document.createElement('DIV')
		ui.style.margin = '0.5rem'
		ui.style.padding = '0.5rem'
		ui.style.border = '0.1rem solid black'
		document.body.appendChild(ui)
		ui.focus()
	},

	accessibility_render_menu_start: function() {
		while (ui.firstChild) {
			ui.removeChild(ui.firstChild)
		}

		const list = document.createElement('UL')
		ui.appendChild(list)
	},

	accessibility_render_menu_item: function(name, hasSubMenu) {
		const list = ui.firstChild
		const listItem = document.createElement('LI')
		const menuButton = document.createElement('BUTTON')
		menuButton.innerText = UTF8ToString(name, 128)
		if (hasSubMenu) menuButton.setAttribute('aria-haspopup', 'true')
		menuButton.setAttribute('tabindex', '-1')
		listItem.appendChild(menuButton)
		list.appendChild(listItem)
	},

	accessibility_render_menu_done: function() {
		//
	},

	accessibility_render_current_item: function(itemNumber) {
		ui.firstChild.children[itemNumber].firstChild.focus()
	}
})
