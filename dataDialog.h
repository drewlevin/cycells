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
 * along with QtCyCells; if not, write to the Free Software Foundation, *
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA        *
 *                                                                      *
 ************************************************************************/
/************************************************************************
 * file dataDialog.h                                                    *
 *                                                                      *
 * Declarations for QtDataDialog class                                  * 
 *                                                                      *
 * Text summary of current cell counts and average molecular            *
 *   concentrations                                                     *
 ************************************************************************/

#ifndef _DATADIALOG_H_
#define _DATADIALOG_H_

#include <vector>
#include <string>

#include <QDialog>
#include <QWidget>
#include <QHeaderView>

#include "ui_DataDialog.h"

class Tissue;
class History;

using namespace std;

class QtDataDialog : public QDialog, private Ui::dlgDataDialog
{
	Q_OBJECT

  public:

		QtDataDialog(QWidget *parent = 0);

    void initialize(const Tissue &tr);
    void update(const History &hr);

  private:

    int m_numCellTypes, m_numMolTypes;
    vector<QString> m_molNames;
    vector<QString> m_cellNames;
    vector<QString> m_attrNames;

};

#endif // _DATADIALOG_H_

