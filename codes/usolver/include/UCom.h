/*---------------------------------------------------------------------------*\
    OneFLOW - LargeScale Multiphysics Scientific Simulation Environment
	Copyright (C) 2017-2019 He Xin and the OneFLOW contributors.
-------------------------------------------------------------------------------
License
    This file is part of OneFLOW.

    OneFLOW is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OneFLOW is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OneFLOW.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/


#pragma once
#include "HXDefine.h"

BeginNameSpace( ONEFLOW )

class BcRecord;

const int F_INNER = 0;
const int F_GHOST = 1;
const int F_TOTAL = 2;

class UGeom
{
public:
    UGeom();
    ~UGeom();
public:
    void Init();
    void CreateBcRegion();
    void SetStEd( int flag );
    void DumpCellFace( int cId );
public:
    int fId;
	int cId;
    int bcfId;
    int nFace;
    int nBFace;
    int nCell;
    int nTCell;
    int ist, ied;
    int lc;
    int rc;
    int ir, bcr, bcdtkey, bctype, nRegion, nRBFace;
    int ireconface;
public:
    IntField * lcf;
    IntField * rcf;
    IntField * blankf;
    LinkField * c2f;

    RealField * fnx;
    RealField * fny;
    RealField * fnz;
    RealField * fvn;
    RealField * farea;

    RealField * fcx;
    RealField * fcy;
    RealField * fcz;

    RealField * fvx;
    RealField * fvy;
    RealField * fvz;

    RealField * cvol, * cvol1, * cvol2;
    RealField * ccx;
    RealField * ccy;
    RealField * ccz;
    BcRecord * bcRecord;
};

extern UGeom ug;

void AddF2CField( MRField * cellField, MRField * faceField );

EndNameSpace