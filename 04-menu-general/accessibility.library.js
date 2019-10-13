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
		let found = null

		for (const child of proxyArea.children) {
			if (child.id === pageId) {
				found = child
			}
			child.hidden = child.id !== pageId
		}

		if (!found) {
			const list = document.createElement('UL')
			list.id = pageId
			proxyArea.appendChild(list)
			pageUnderConstruction = list
		}
	},

	accessibility_render_page_item: function(name, hasSubPage) {
		if (pageUnderConstruction) {
			const listItem = document.createElement('LI')
			const pageButton = document.createElement('BUTTON')
			pageButton.innerText = UTF8ToString(name, 128)  // eslint-disable-line
			if (hasSubPage) pageButton.setAttribute('aria-haspopup', 'true')
			pageButton.setAttribute('tabindex', '-1')
			listItem.appendChild(pageButton)
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
