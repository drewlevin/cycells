/************************************************************************
 *                                                                      *
 * Copyright (C) 2004  Christina Warrender and Drew Levin               *
 *                                                                      *
 * This file is part of QtCyCells.                                      *
 *                                                                      *
 * QtCyCells is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * QtCyCells is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with CyCells; if not, write to the Free Software Foundation,   *
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA        *
 *                                                                      *
 ************************************************************************/
/************************************************************************
 * file dataDialog.cc                                                   *
 *                                                                      *
 * Definitions for QtDataDialog class                                   * 
 *                                                                      *
 * Text summary of current cell counts and average molecular            *
 *   concentrations                                                     *
 ************************************************************************/

#include "dataDialog.h"
#include "tissue.h"
#include "history.h"
#include "cellType.h"
#include "cell.h"

QtDataDialog::QtDataDialog(QWidget *parent) 
	: QDialog(parent)
{
	// Initialize the Dialog Form defined in ui_DataDialog.h
	setupUi(this);
}

/************************************************************************ 
 * initialize()                                                         *
 *   Initializes the DataDialog window which tracks molecule and cell   *
 * quantities                                                           *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
void QtDataDialog::initialize(const Tissue &tr)
{
	QTableWidgetItem *widgetItem;

	int totalAttributes = 0;

  // empty vectors in case this is a redefinition
  m_cellNames.clear();
  m_attrNames.clear();
  m_molNames.clear();

  // get cell/attr/molecule type names for future reference
  m_numMolTypes = tr.getNumMolTypes();
  for (int i=0; i<m_numMolTypes; i++)
    m_molNames.push_back(QString(tr.getMolecule(i).getName().c_str()));

  m_numCellTypes = tr.getNumCellTypes();
  for (int i=0; i<m_numCellTypes; i++)
  {
    const CellType *pct = tr.getCellType(i);
    m_cellNames.push_back(QString(pct->getName().c_str()));
    for (int j=0; j<pct->getNumAttributes(); j++) {
      m_attrNames.push_back(QString(pct->getAttributeName(j).c_str()));
			totalAttributes++;
		}
  }
	
	// Initialize Tables
	tblMolType->setRowCount(m_numMolTypes);
	tblCellType->setRowCount(m_numCellTypes);
	tblAttributes->setRowCount(totalAttributes);

	tblMolType->horizontalHeader()->setStretchLastSection(true);
	tblCellType->horizontalHeader()->setStretchLastSection(true);
	tblAttributes->horizontalHeader()->setStretchLastSection(true);

	// Initialize Cells within the Tables
	for (int i=0; i<m_numMolTypes; i++) {
		widgetItem = new QTableWidgetItem();
		tblMolType->setItem(i, 0, widgetItem);
		widgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	
		widgetItem = new QTableWidgetItem();
		tblMolType->setItem(i, 1, widgetItem);
		widgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}

	for (int i=0; i<m_numCellTypes; i++) {
		widgetItem = new QTableWidgetItem();
		tblCellType->setItem(i, 0, widgetItem);
		widgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		widgetItem = new QTableWidgetItem();
		tblCellType->setItem(i, 1, widgetItem);
		widgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}

	for (int i=0; i<totalAttributes; i++) {
		widgetItem = new QTableWidgetItem();
		tblAttributes->setItem(i, 0, widgetItem);
		widgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	
		widgetItem = new QTableWidgetItem();
		tblAttributes->setItem(i, 1, widgetItem);
		widgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		widgetItem = new QTableWidgetItem();
		tblAttributes->setItem(i, 2, widgetItem);
		widgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}
}

/************************************************************************ 
 * update()                                                             *
 *   Updates the values in the DataDialog window                        *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
void QtDataDialog::update(const History &hr)
{
	QString str;
	QTableWidgetItem *txt;

  // Molecules 
  for (int i=0; i<m_numMolTypes; i++)  {
		txt = tblMolType->item(i, 0);
		txt->setText(m_molNames[i]);

		str.sprintf("%.1e", hr.getCurrentConc(i));
		txt = tblMolType->item(i, 1);
		txt->setText(str);
  }

	// Cells and Attributes
  int k = 0;
  for (int i=0; i<m_numCellTypes; i++)
  {
		txt = tblCellType->item(i, 0);
		txt->setText(m_cellNames[i]);

		str.sprintf("%d", hr.getCurrentCount(i));
		txt = tblCellType->item(i, 1);
		txt->setText(str);

    const vector<double>& totals = hr.getTotals(i);
    for (unsigned int j=0; j<totals.size(); j++)
    {
			if (j == 0) {
				txt = tblAttributes->item(k, 0);
				txt->setText(m_cellNames[i]);
			}

			txt = tblAttributes->item(k, 1);
			txt->setText(m_attrNames[k]);

			str.sprintf("%g", totals[j]);
			txt = tblAttributes->item(k, 2);
			txt->setText(str);

      k++;
    }
  }
}

