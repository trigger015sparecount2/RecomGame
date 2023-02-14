//---------------------------
//Author:�O��q��
//���[�h����(load.cpp)
//---------------------------
#include "load.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "field.h"
#include "light.h"
#include "fade.h"
#include "camera.h"
#include "scene.h"
#include "wall.h"
#include "player.h"
#include "sky.h"

CLoad::CLoad()
{

}

CLoad::~CLoad(void)
{

}

//�ǂݍ���
void CLoad::Load(const char *aFileName)
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];
	char aPlayerFile[256];
	int nNumModel;
	int nCntModel = 0;
	bool bField = false;
	bool bWall = false;
	bool bModel = false;
	bool bLight = false;
	bool bCamera = false;
	bool bBillboard = false;
	bool bjump = false;
	bool bCheck = false;
	bool bCameraPanel = false;
	bool bPlayer = false;
	bool bGoal = false;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nTex;
	int nBlock[2];
	D3DXVECTOR3 size;
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nMoveTime = 0;
	int nType;
	CScene::COLLISION collision;
	int nCollision;
	int nCntLight = 0;
	D3DXCOLOR col;
	D3DXVECTOR3 vec;
	D3DXVECTOR2 Tex;
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posR;
	int nJump = -1;
	int nZipLine = -1;
	int nCheck = -1;
	int nDrop = -1;
	bool bDrop = false;
	bool bSky = false;
	float fScroll;
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanf���J��Ԃ��ăt�@�C����ǂݎ���Ă���
			if (strcmp(&aFile[0], "NUM_MODEL") == 0) //���f����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nNumModel);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0) //���f����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				//CObject::Load(nCntModel, aFile);
				nCntModel++;
			}

			if (strcmp(&aFile[0], "FIELDSET") == 0) //�n��
			{
				bField = true;
			}
			if (strcmp(&aFile[0], "END_FIELDSET") == 0) //�n��
			{
				size.x = Tex.x * nBlock[0];
				size.z = Tex.y * nBlock[1];
				size.y = -sinf(rot.x) * size.z;
				//size.y = 0.0f;
				CField::Create(size, pos, nTex, Tex, true);
				bField = false;
			}
			if (strcmp(&aFile[0], "WALLSET") == 0) //��
			{
				bWall = true;
			}
			if (strcmp(&aFile[0], "END_WALLSET") == 0) //��
			{
				size.x = Tex.x * nBlock[0];
				size.y = Tex.y * nBlock[1];
				size.z = 0.0f;
				CWall::Create(size, pos, nTex, Tex, rot);
				bWall = false;
			}
			if (strcmp(&aFile[0], "MODELSET") == 0) //�I�u�W�F�N�g
			{
				bModel = true;
			}
			if (strcmp(&aFile[0], "END_MODELSET") == 0) //�I�u�W�F�N�g
			{
				//CObject::Create(pos, nType, collision, rot, nMoveTime, move, bDrop);
				nMoveTime = 0;
				move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				bDrop = false;
				nDrop = -1;
				bModel = false;
			}
			if (strcmp(&aFile[0], "LIGHTSET") == 0) //���C�g
			{
				bLight = true;
			}
			if (strcmp(&aFile[0], "END_LIGHTSET") == 0) //���C�g
			{
				CLight::Create(col, vec, nCntLight);
				nCntLight++;
				bLight = false;
			}
			if (strcmp(&aFile[0], "CAMERASET") == 0) //�J����
			{
				bCamera = true;
			}
			if (strcmp(&aFile[0], "END_CAMERASET") == 0) //�J����
			{
				bCamera = false;
			}
			if (strcmp(&aFile[0], "PLAYERSET") == 0) //�v���C���[
			{
				bPlayer = true;
			}
			if (strcmp(&aFile[0], "END_PLAYERSET") == 0) //�v���C���[
			{
				CPlayer::Create(pos, rot, aPlayerFile);
				bPlayer = false;
			}
			if (strcmp(&aFile[0], "SKYSET") == 0) //��
			{
				bSky = true;
			}
			if (strcmp(&aFile[0], "END_SKYSET") == 0) //��
			{
				CSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.00002f, CPlane::GetTexture(6));
				bSky = false;
			}
			if (bField == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //�ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //�p�x
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
				if (strcmp(&aFile[0], "BLOCK") == 0) //�e�N�X�`���ׂ̍���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &Tex.x, &Tex.y);
				}
				if (strcmp(&aFile[0], "SIZE") == 0) //�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d %d", &nBlock[0], &nBlock[1]);
				}
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //�e�N�X�`��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
			}
			if (bWall == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //�ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //��]
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
				if (strcmp(&aFile[0], "BLOCK") == 0) //�e�N�X�`���ׂ̍���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &Tex.x, &Tex.y);
				}
				if (strcmp(&aFile[0], "SIZE") == 0) //�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d %d", &nBlock[0], &nBlock[1]);
				}
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //�e�N�X�`��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
			}
			if (bBillboard == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //�ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "SIZE") == 0) //�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &size.x, &size.y);
					size.z = 0.0f;
				}
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //�e�N�X�`��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
			}
			if (bModel == true)
			{
				if (strcmp(&aFile[0], "JUMP") == 0) //�g�����|�����p
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nJump);
					if (nJump == 1)
					{
						bjump = true;
					}
				}
				if (strcmp(&aFile[0], "CHECK") == 0) //�`�F�b�N�|�C���g�p
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nCheck);
					if (nCheck == 1)
					{
						bCheck = true;
						nCheck = -1;
					}
				}
				if (strcmp(&aFile[0], "ZIP") == 0) //�X���b�N���C���p
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nZipLine);
				}
				if (strcmp(&aFile[0], "MOVETIME") == 0) //�ړ�����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nMoveTime);
				}
				if (strcmp(&aFile[0], "MOVE") == 0) //�ړ�����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &move.x, &move.y, &move.z);
				}
				if (strcmp(&aFile[0], "TYPE") == 0) //���f���̎��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nType);
				}
				if (strcmp(&aFile[0], "POS") == 0) //���f���̏ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //���f���̕���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
				if (strcmp(&aFile[0], "COL") == 0) //���f���̓����蔻��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nCollision);
					switch (nCollision)
					{
					case 0:
						collision = CScene::COLLISION_SPHERE;
						break;
					case 1:
						collision = CScene::COLLISION_SQUARE;
						break;
					default:
						break;
					}
				}
				if (strcmp(&aFile[0], "DROP") == 0) //�������邩
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nDrop);
					if (nDrop == 1)
					{
						bDrop = true;
					}
				}
			}
			if (bLight == true)
			{
				if (strcmp(&aFile[0], "DIRECTION") == 0) //���̕���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &vec.x, &vec.y, &vec.z);
				}
				if (strcmp(&aFile[0], "DIFFUSE") == 0) //���̐F
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &col.r, &col.g, &col.b);
					col.a = 1.0f;
				}
			}
			if (bCamera == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //���_
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
					CManager::GetRenderer()->GetCamera()->SetPosV(pos);
				}
				if (strcmp(&aFile[0], "REF") == 0) //�����_
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
					CManager::GetRenderer()->GetCamera()->SetPosR(pos);
				}
			}
			if (bSky == true)
			{
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //�e�N�X�`��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
				if (strcmp(&aFile[0], "MOVE") == 0) //����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fScroll);
				}
			}
			if (bCameraPanel == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //�p�l���̐ݒu�ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "SIZE") == 0) //�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &size.x, &size.y, &size.z);
				}
				if (strcmp(&aFile[0], "POSV") == 0) //�J�����̎��_
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &posV.x, &posV.y, &posV.z);
				}
				if (strcmp(&aFile[0], "POSR") == 0) //�J�����̒����_
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &posR.x, &posR.y, &posR.z);
				}
			}
			if (bPlayer == true)
			{
				if (strcmp(&aFile[0], "MOTION_FILENAME") == 0) //���f���̏ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%s", &aPlayerFile[0]);
				}
				if (strcmp(&aFile[0], "POS") == 0) //���f���̏ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //���f���̕���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
			}
			if (bGoal == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //�S�[���̏ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "SIZE") == 0) //�S�[���̑傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &size.x, &size.z);
					size.y = 0.0f;
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //�I���
			{
				break;
			}
		}
	}
}